/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "FPEC_interface.h"
#include "UART_interface.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */
void Parser_voidParseRecord(u8* Copy_u8BufData);

volatile u8  u8ReceiverBuffer[100] ;
volatile u8  u8ReceiverCounter    = 0;
volatile u8  u8TimeOutFlag        = 0;
volatile u8  u8WriteRequest       = 1;
typedef void (*Function_t)(void);
Function_t AddrressCall = 0;

void Receive_Record(void);

void JumpApplicationFunction(void)
{
	/* definition of scb_vtor Register to make startup code initialized vector table of Application */
	#define SCB_VTOR   *((volatile u32*)0xE000ED08)
	/* Store the first Address of Flash to be the Address of Vector Table */
	SCB_VTOR = 0x08001000;
	/* Initialize a pointer to function with address of startup code */
	/* Jump to the next Address to Start Startup Code */
	AddrressCall = *(Function_t*)(0x08001004);
	AddrressCall();
}

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



uint32_t time_ms=0 ;


CAN_TxHeaderTypeDef TxHeader[3] ;
uint32_t TxMailBox[3];
uint8_t  TxData[8] = {5 , 250};

CAN_RxHeaderTypeDef RxHeader ;
uint8_t RxData[8];

/////////////////////////////////////////////////////////////////////////////////////////
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	u8ReceiverBuffer[u8ReceiverCounter] = RxData[0] ;
	GPIO_VidSetPinDirection( GPIOA , PIN0 , OUTPUT_SPEED_2MHZ_PP );
	GPIO_VidSetPinValue( GPIOA , PIN0 , LOW );
	if(RxHeader.StdId == 0x222)//id of data message
	{
		static u8 L_u8Flag = 0 ;
		if(L_u8Flag == 0)
		{
			GPIO_VidSetPinValue( GPIOA , PIN1 , HIGH );
			L_u8Flag = 1;
		}
		else
		{
			GPIO_VidSetPinValue( GPIOA , PIN1 , LOW );
			L_u8Flag = 0;
		}
		Receive_Record();
		//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
}
////////////////////////////////////////////////////////////////////////////////////////

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	/* Initialize RCC peripheral --> HSI Clock */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,RCC_GPIOA);  /* Initialize Clock --> PortA  peripheral */
	RCC_voidEnableClock(RCC_AHB,RCC_FPEC);   /* Initialize Clock --> FPEC   peripheral */
	/* Initialize Systick peripheral to be run on 1MHZ Clock */
	SYSTICK_voidInit();
	/* Define an Interval 15 second if this Interval end the CPU will jump to Application Function */
	SYSTICK_voidSetIntervalSingle(15000000,JumpApplicationFunction);

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CAN_Init();
	/* USER CODE BEGIN 2 */

	HAL_CAN_Start(&hcan);

	////////////////////////////////////////////////////////////////////////////////////////
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); // active Rx Interrupt
	////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	TxHeader[0].StdId = 0x111 ;
	TxHeader[0].DLC   = 8     ;
	TxHeader[0].ExtId = 0     ;
	TxHeader[0].RTR   = CAN_RTR_DATA ;
	TxHeader[0].IDE   = CAN_ID_STD   ;
	TxHeader[0].TransmitGlobalTime = DISABLE ;
	//////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////
	TxHeader[1].StdId = 0x333 ;
	TxHeader[1].ExtId = 0     ;
	TxHeader[1].RTR   = CAN_RTR_DATA ;
	TxHeader[1].IDE   = CAN_ID_STD   ;
	TxHeader[1].DLC   = 8            ;
	TxHeader[1].TransmitGlobalTime = DISABLE ;
	/////////////////////////////////////////////////////////////////////////////////////////

	/* USER CODE END 2 */

	/* Send Acknowledge to the Master That indicate we are ready to receive the new update of Application Code */
		TxData[0] = 'r';
		HAL_CAN_AddTxMessage(&hcan, &TxHeader[0], TxData, &TxMailBox[0]);// r message
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1)
	{

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief CAN Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN_Init(void)
{

	/* USER CODE BEGIN CAN_Init 0 */

	/* USER CODE END CAN_Init 0 */

	/* USER CODE BEGIN CAN_Init 1 */

	/* USER CODE END CAN_Init 1 */
	hcan.Instance = CAN1;
	hcan.Init.Prescaler = 4;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_2TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = DISABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CAN_Init 2 */
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CAN_FilterTypeDef Filter1Confg ;

	Filter1Confg.FilterActivation = CAN_FILTER_ENABLE ;
	Filter1Confg.FilterBank = 0 ;    // select the FilterBank id you will use  0 to SlaveStartFilterBank
	Filter1Confg.FilterFIFOAssignment = CAN_FILTER_FIFO0  ;  // which FIFO this filter work on
	Filter1Confg.FilterIdHigh = 0x000 ;  // here is 16 bit but we will use only 11bit>>STD_ID  so value<5
	Filter1Confg.FilterIdLow  = 0x000 ;  // for ExtId , RTR and IDE  && check data sheet &&
	Filter1Confg.FilterMaskIdHigh = 0x000 ;  //16 bit but we will use only 11bit>>STD_ID  so value<5
	Filter1Confg.FilterMaskIdLow  = 0x000  ;  // for ExtId , RTR and IDE   check data sheet
	Filter1Confg.FilterMode = CAN_FILTERMODE_IDMASK ;
	Filter1Confg.FilterScale = CAN_FILTERSCALE_32BIT ;
	Filter1Confg.SlaveStartFilterBank = 13 ;

	HAL_CAN_ConfigFilter(&hcan, &Filter1Confg);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/* USER CODE END CAN_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

	/*Configure GPIO pin : PC13 */
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

void Receive_Record(void)
{

	/* Stop Timer to avoid interrupt of systick while receiving data from master */
	SYSTICK_voidStopInterval();
	/*receive data and check it if it equal '\n' that indicate we receive a fully Record */
	/* if it not equal '\n' that indicate we need to increment counter of Buffer receiver to receive the next byte of record */
	if(u8ReceiverBuffer[u8ReceiverCounter] == '\n')
	{
		/* After receive first record and Before Flashing it on Flash memory */
		/* we need to Erase Application Area to be able to write on flash memory*/
		/* write Request change only when receive first record */
		if (u8WriteRequest == 1)
		{
			FPEC_voidEraseAppArea();
			u8WriteRequest = 0;
		}
		/* Parse the record which is saved in Receiver Buffer to be Suitable to Flashing on Flash memory */
		Parser_voidParseRecord(u8ReceiverBuffer);
		/* Send an acknowledge to the master that indicate we receive fully record and finish flashing it */
		TxData[0] = 'o' ;
		HAL_CAN_AddTxMessage(&hcan, &TxHeader[1], TxData, &TxMailBox[1]);// 'o' message
		/* reset receiver counter to receive the next record */
		u8ReceiverCounter = 0;
	}
	else
	{
		u8ReceiverCounter ++ ;
	}
	if(u8ReceiverBuffer[8] == '1')
	{
		JumpApplicationFunction();
	}
	/* Define an Interval 15 second if this Interval end the CPU will jump to Application Function */
	SYSTICK_voidSetIntervalSingle(15000000,JumpApplicationFunction);
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
