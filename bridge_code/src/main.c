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
#include "FPEC_interface.h"
#include "UART_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint16_t time_ms = 0 ;
CAN_TxHeaderTypeDef TxHeader[3];
CAN_RxHeaderTypeDef RxHeader ;

CAN_HandleTypeDef hcan;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile u8  u8SendBuffer[100]       ; 								/** u8ReceiverBuffer send buffer of 100 elements to send massge from Bridge   */

volatile u8  u8ReceiverBuffer[100]   ;								/** u8ReceiverBuffer receive buffer of 100 elements to receive record from PC   */

volatile u8  u8ReceiverCounter    = 0;								/**u8ReceiverCounter receive counter elements of 100 elements */

volatile u8  u8WriteRequest       = 1;								/** u8WriteRequest change only when receive first record.After receive first record 
																		and Before Flashing it on Flash memory we need to Erase Application Area to be able to write on flash memory */
volatile u32 Start_Address_of_APP = 0x08007800  ;  					/** First Address of Page 30 */
volatile u8  u8SendCounter    = 0;
volatile u32 Start_Address_of_APP_Sender = 0x08007800  ;  			/**First Address of Page 30 */

uint32_t TxMailBox[3];  /** Array of 3 CAN mail Box   */ 
uint8_t  TxData[8] = {10 , 250}; /** Array of 8 byte with initial values   */ 
uint8_t RxData[8];

/**private functions for SystemClock_Config , GPIO_Init, and CAN_Init  */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void Send_Record(void);
/* USER CODE END PFP */

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  The Callback function that calls when ISR executes.
  *	@param  CAN_HandleTypeDef *hcan is Pointer to Structe config which CAN will use .
  * @return None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0 , &RxHeader, RxData); /**CAN_RX_FIFO0 is a buffre which recive data entry ,RxHeader is return the header of coming 
																	data ,* RxData is the coming data */
    Send_Record();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  The application entry point.
  *	@param  None 
  * @return int
  */
int main(void)
{
    u8 Local_u8ReceiverStatus;

    /* Initialize RCC peripheral --> HSI Clock */
    RCC_voidInitSysClock();
    RCC_voidEnableClock(RCC_APB2,RCC_UART1); /* Initialize Clock --> USART1 peripheral */
    RCC_voidEnableClock(RCC_APB2,RCC_GPIOA);  /* Initialize Clock --> PortA  peripheral */
    RCC_voidEnableClock(RCC_AHB,RCC_FPEC);   /* Initialize Clock --> FPEC   peripheral */
    /* Configure  pin 9  port A To be a TX pin of UART peripheral  */
    GPIO_VidSetPinDirection(DIOA,PIN9,OUTPUT_SPEED_2MHZ_AFPP);
    /* Configure  pin 10  port A To be an RX pin of UART peripheral */
    GPIO_VidSetPinDirection(DIOA,PIN10,INPUT_FLOATING);
    /* Initialize UART peripheral "Enable TX & & RX & peripheral " */
    UART1_voidInit();

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_CAN_Init();

    HAL_CAN_Start(&hcan);

    /////////////////////////////////////////////////////////////////////////////////////////
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
    /////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////
    TxHeader[0].StdId = 0x222 ;
    TxHeader[0].ExtId = 0     ;
    TxHeader[0].RTR   = CAN_RTR_DATA ;
    TxHeader[0].IDE   = CAN_ID_STD   ;
    TxHeader[0].DLC   = 8            ;
    TxHeader[0].TransmitGlobalTime = DISABLE ;
    /////////////////////////////////////////////////////////////////////////////////////////

    /* Infinite loop */
    while (1)
    {
        /* USER CODE END WHILE */
        Local_u8ReceiverStatus = UART1_u8Receive( &(u8ReceiverBuffer[u8ReceiverCounter]) );
        /* Check the received data if it is 'r' which is acknowledge from slave that means slave is ready to receive  */
        /* or the received data is a new application*/
        if(Local_u8ReceiverStatus == 1)
        {
            /*receive data and check it if it equals '\n' that indicates we receive a fully Record */
            /* if it not equal '\n' that indicates we need to increment counter of Buffer receiver to receive the next byte of record */
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
                /* Flash the record which is saved in Receiver Buffer to be Suitable to send to the slave */
                FPEC_voidFlashWrite(&Start_Address_of_APP , u8ReceiverBuffer , u8ReceiverCounter);
                /* Send an acknowledge to the master that indicates we receive a fully record and finish flashing it */
                UART1_voidTransmit("ok");
                /* reset receiver counter to receive the next record */
                u8ReceiverCounter = 0;
            }
            else
            {
                u8ReceiverCounter ++ ;
            }
        }
        else
        {

        }
    }
}

/**
  * @brief System Clock Configuration
  *	@param  None
  * @return None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    /** Initializes the CPU, AHB and APB buses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
}

/**
  * @brief CAN Initialization Function
  *	@param  None
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
    hcan.Init.AutoBusOff = DISABLE;
    hcan.Init.AutoWakeUp = DISABLE;
    hcan.Init.AutoRetransmission = DISABLE;
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAN_FilterTypeDef Filter1Confg ;

    Filter1Confg.FilterActivation = CAN_FILTER_ENABLE ;
    Filter1Confg.FilterBank = 0 ;    // select the FilterBank id you will use  0 to SlaveStartFilterBank
    Filter1Confg.FilterFIFOAssignment = CAN_FILTER_FIFO0  ;  // which FIFO this filter work on
    Filter1Confg.FilterIdHigh = 0 ;  // here is 16 bit but we will use only 11bit>>STD_ID  so value<5
    Filter1Confg.FilterIdLow  = 0 ;  // for ExtId , RTR and IDE  && check data sheet &&
    Filter1Confg.FilterMaskIdHigh = 0 ;  //16 bit but we will use only 11bit>>STD_ID  so value<5
    Filter1Confg.FilterMaskIdLow  = 0  ;  // for ExtId , RTR and IDE   check data sheet
    Filter1Confg.FilterMode = CAN_FILTERMODE_IDMASK ;
    Filter1Confg.FilterScale = CAN_FILTERSCALE_32BIT ;
    Filter1Confg.SlaveStartFilterBank = 13 ;

    HAL_CAN_ConfigFilter(&hcan, &Filter1Confg);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  * @brief  Transmit the record data to the slave using CAN protocol.
  *
  * This function reads data from the flash memory and transmits it to the slave
  * using the CAN protocol. It collects a record from the flash memory until
  * the '/n' character is encountered, indicating the end of the record.
  *
  * @param  None
  * @retval None
  */

void Send_Record(void)
{
    while(1)
    {
        u8SendBuffer[u8SendCounter] = *((u8*)Start_Address_of_APP_Sender) ;
        if(u8SendBuffer[u8SendCounter] == '/n')
        {

            /* transmit data to slave */
            for(int Local_u8DataCounter = 0 ; Local_u8DataCounter <= u8SendCounter ; Local_u8DataCounter++)
            {
                TxData[0] = u8SendBuffer[Local_u8DataCounter];
                HAL_CAN_AddTxMessage(&hcan, &TxHeader[0], TxData, &TxMailBox[0]); //send data
            }
            /* reset sender counter to collect the next record */
            u8SendCounter = 0 ;
            if(u8SendBuffer[8] != '1')
            {
                Start_Address_of_APP_Sender ++ ;
            }
            else
            {
                Start_Address_of_APP_Sender = 0x08007800  ;
            }
            break;
        }
        else
        {
            u8SendCounter ++ ;
            Start_Address_of_APP_Sender ++ ;
        }
    }
}
