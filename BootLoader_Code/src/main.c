
/*****************************************/
/* SWC       : Bridge Code               */
/* Layer     : Application               */
/* Version   : 1.0                       */
/* Date      : 18/10/2023		         */
/* Last Edit : N/A                       */
/*****************************************/
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "FPEC_interface.h"
#include "UART_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef void (*Function_t)(void);

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
CAN_RxHeaderTypeDef RxHeader ;

CAN_HandleTypeDef hcan;

volatile u8  u8ReceiverBuffer[100]   ;                         /** u8ReceiverBuffer receive buffer of 100 elements to receive record from PC   */

volatile u8  u8ReceiverCounter    = 0;                         /**u8ReceiverCounter receive counter elements of 100 elements */

volatile u8  u8WriteRequest       = 1;                         /** u8WriteRequest change only when receive first record. After receiving the first record 
                                                                    and before Flashing it on Flash memory, we need to Erase Application Area to be able to write on flash memory */

CAN_TxHeaderTypeDef TxHeader[3] ;                             
                                                                 
uint32_t TxMailBox[3];                                          /** Array of 3 CAN mailboxes   */ 
uint8_t  TxData[8] = {'r','o'};                                 /** Array of 8 bytes to transmit with initial values   */ 
uint8_t RxData[8];                                               /** Array of 8 bytes with initial values to receive   */ 

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void Receive_Record(void);
void Parser_voidParseRecord(u8* Copy_u8BufData);
Function_t AddrressCall = 0;

/** Private functions for SystemClock_Config, GPIO_Init, and CAN_Init  */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE END PFP */

//////////////////////////////////////////////////
/**
  * @brief  Jumps to the application function after a specified interval.
  * @note   This function is called by the SysTick timer when the specified interval elapses.
			and initializes the Vector Table of the application and jumps to the application code.
  *	@param  None
  * @return None
  */
void JumpApplicationFunction(void)
{
    /* Definition of SCB_VTOR Register to make startup code initialize the vector table of the Application */
    #define SCB_VTOR   *((volatile u32*)0xE000ED08)
    /* Store the first Address of Flash to be the Address of the Vector Table */
    SCB_VTOR = 0x08007800;
    /* Initialize a pointer to a function with the address of the startup code */
    /* Jump to the next Address to Start the Startup Code */
    AddrressCall = *(Function_t*)(0x08007804);
    AddrressCall();
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Handles reception of CAN messages and triggers the record parsing process.
 * @param hcan: pointer to a CAN_HandleTypeDef structure.
 * @return None
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
    u8ReceiverBuffer[u8ReceiverCounter] = RxData[0] ;
    GPIO_VidSetPinDirection( DIOA , PIN0 , OUTPUT_SPEED_2MHZ_PP );
    GPIO_VidSetPinValue( DIOA , PIN0 , LOW );

    if(RxHeader.StdId == 0x222)//id of data message
    {
        static u8 L_u8Flag = 0 ;
        if(L_u8Flag == 0)
        {
            GPIO_VidSetPinValue( DIOA , PIN1 , HIGH );
            L_u8Flag = 1;
        }
        else
        {
            GPIO_VidSetPinValue( DIOA , PIN1 , LOW );
            L_u8Flag = 0;
        }
        Receive_Record();
    }
}
////////////////////////////////////////////////////////////////////////////////////////

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 *	@param None
 * @return int
 */
int main(void)
{
    /* Initialize RCC peripheral --> HSI Clock */
    RCC_voidInitSysClock();
    RCC_voidEnableClock(RCC_APB2,RCC_GPIOA);  /* Initialize Clock --> PortA  peripheral */
    RCC_voidEnableClock(RCC_AHB,RCC_FPEC);   /* Initialize Clock --> FPEC   peripheral */
    /* Initialize Systick peripheral to be run on 1MHz Clock */
    SYSTICK_voidInit();
    /* Define an Interval 15 seconds; if this Interval ends, the CPU will jump to the Application Function */
    SYSTICK_voidSetIntervalSingle(15000000,JumpApplicationFunction);

    /* MCU Configuration--------------------------------------------------------*/

    /* Initialize all configured peripherals */
	MX_GPIO_Init();   // Initialize GPIO pins and settings
	MX_CAN_Init();    // Initialize CAN peripheral settings and filters

	HAL_CAN_Start(&hcan);  // Start CAN peripheral operation

	////////////////////////////////////////////////////////////////////////////////////////
	// Activate CAN receive (Rx) interrupt to be notified when a message is pending in FIFO0.
	// This enables the system to react to incoming messages.
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Configure CAN transmission parameters for the first CAN message (TxHeader[0]).
	TxHeader[0].StdId = 0x111 ;               // Standard identifier for the CAN message.
	TxHeader[0].DLC   = 8     ;               // Data Length Code: Number of bytes in the data field (8 bytes).
	TxHeader[0].ExtId = 0     ;               // Extended identifier for the CAN message (not used in this case).
	TxHeader[0].RTR   = CAN_RTR_DATA ;        // Remote Transmission Request: Data frame (not a remote frame).
	TxHeader[0].IDE   = CAN_ID_STD   ;        // Identifier Type: Standard (11-bit) identifier.
	TxHeader[0].TransmitGlobalTime = DISABLE; // Disable the inclusion of the transmit time in the message.
	//////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// Configure CAN transmission parameters for the second CAN message (TxHeader[1]).
TxHeader[1].StdId = 0x333 ;               // Standard identifier for the CAN message.
TxHeader[1].ExtId = 0     ;               // Extended identifier for the CAN message (not used in this case).
TxHeader[1].RTR   = CAN_RTR_DATA ;        // Remote Transmission Request: Data frame (not a remote frame).
TxHeader[1].IDE   = CAN_ID_STD   ;        // Identifier Type: Standard (11-bit) identifier.
TxHeader[1].DLC   = 8            ;        // Data Length Code: Number of bytes in the data field (8 bytes).
TxHeader[1].TransmitGlobalTime = DISABLE; // Disable the inclusion of the transmit time in the message.
/////////////////////////////////////////////////////////////////////////////////////////


    /* USER CODE END 2 */

    /* Send Acknowledge to the Master That indicates we are ready to receive the new update of Application Code */
    TxData[0] = 'r';
    HAL_CAN_AddTxMessage(&hcan, &TxHeader[0], TxData, &TxMailBox[0]); // r message
    /* Infinite loop */

    while (1)
    {

    }
}

/**
 * @brief System Clock Configuration
 * @note This function initializes the RCC Oscillators and configures the CPU, AHB, and APB buses clocks.
 * @param None
 * @return None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.*/
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    /** Initializes the CPU, AHB, and APB buses clocks*/
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

}

/**
 * @brief CAN Initialization Function
 * @note This function configures the CAN1 instance, sets the prescaler, mode, and filter settings.
 * @param  None
 * @return None
 */
static void MX_CAN_Init(void)
{
    hcan.Instance = CAN1;
    hcan.Init.Prescaler = 4;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_BS1_2TQ;
    hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
    hcan.Init.TimeTriggeredMode = DISABLE;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAN_FilterTypeDef Filter1Confg ;

    Filter1Confg.FilterActivation = CAN_FILTER_ENABLE ;
    Filter1Confg.FilterBank = 0 ;    // select the FilterBank id you will use  0 to SlaveStartFilterBank
    Filter1Confg.FilterFIFOAssignment = CAN_FILTER_FIFO0  ;  // which FIFO this filter works on
    Filter1Confg.FilterIdHigh = 0x000 ;  // here is 16 bits but we will use only 11 bits >> STD_ID  so value < 5
    Filter1Confg.FilterIdLow  = 0x000 ;  // for ExtId , RTR and IDE  && check data sheet &&
    Filter1Confg.FilterMaskIdHigh = 0x000 ;  //16 bits but we will use only 11 bits >> STD_ID  so value < 5
    Filter1Confg.FilterMaskIdLow  = 0x000  ;  // for ExtId , RTR, and IDE   check data sheet
    Filter1Confg.FilterMode = CAN_FILTERMODE_IDMASK ;
    Filter1Confg.FilterScale = CAN_FILTERSCALE_32BIT ;
    Filter1Confg.SlaveStartFilterBank = 13 ;

    HAL_CAN_ConfigFilter(&hcan, &Filter1Confg);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @return None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

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

}

/**
 * @brief Handles the process of receiving records.
 * @note This function stops the timer to avoid systick interrupts during data reception.
 *       It checks if the received data is a complete record (indicated by '\n').
 *       If a complete record is received, it erases the application area before parsing and flashing.
 *       An acknowledgment is sent to the master, and the receiver counter is reset for the next record.
 *       If the received data contains '1' at index 8, it jumps to the application function after processing.
 *       A 15-second interval is set, and if it expires, the CPU jumps to the application function.
 * @param  None
 * @return None
 */

void Receive_Record(void)
{

    /* Stop Timer to avoid the interrupt of systick while receiving data from the master */
    SYSTICK_voidStopInterval();
    /* Receive data and check if it equals '\n' that indicates we received a fully Record */
    /* If it does not equal '\n' that indicates we need to increment the counter of Buffer receiver to receive the next byte of the record */
    if(u8ReceiverBuffer[u8ReceiverCounter] == '\n')
    {
        /* After receiving the first record and before Flashing it on Flash memory */
        /* we need to Erase Application Area to be able to write on flash memory*/
        /* write Request changes only when receive the first record */
        if (u8WriteRequest == 1)
        {
            FPEC_voidEraseAppArea();
            u8WriteRequest = 0;
        }
        /* Parse the record which is saved in Receiver Buffer to be Suitable for Flashing on Flash memory */
        Parser_voidParseRecord(u8ReceiverBuffer);
        /* Send an acknowledge to the master that indicates we received the fully record and finish flashing it */
        TxData[0] = 'o' ;
        HAL_CAN_AddTxMessage(&hcan, &TxHeader[1], TxData, &TxMailBox[1]);// 'o' message
        /* Reset receiver counter to receive the next record */
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
    /* Define an Interval 15 seconds; if this Interval ends, the CPU will jump to the Application Function */
    SYSTICK_voidSetIntervalSingle(15000000,JumpApplicationFunction);
}
