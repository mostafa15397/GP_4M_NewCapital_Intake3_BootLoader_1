/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :main                        */
/*Layer     :APP                         */
/*Version   :1.1                         */
/*Date      :September 15,2023           */
/*Last Edit :October   30,2023           */
/*****************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "FPEC_interface.h"
#include "UART_interface.h"

void Parser_voidParseRecord(u8* Copy_u8BufData);

volatile u8  u8ReceiverBuffer[100]   ;
volatile u8  u8ReceiverCounter    = 0;
volatile u8  u8TimeOutFlag        = 0;
volatile u8  u8WriteRequest       = 1;
typedef void (*Function_t)(void);
Function_t AddrressCall = 0;

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

void main(void)
{
	u8 Local_u8ReceiverStatus;
	/* Initialize RCC peripheral --> HSI Clock */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,RCC_UART1); /* Initialize Clock --> USART1 peripheral */
	RCC_voidEnableClock(RCC_APB2,RCC_GPIOA);  /* Initialize Clock --> PortA  peripheral */
	RCC_voidEnableClock(RCC_AHB,RCC_FPEC);   /* Initialize Clock --> FPEC   peripheral */
	/* Configure  pin 9  port A To be a TX pin of UART peripheral  */
	GPIO_VidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_2MHZ_AFPP);
	/* Configure  pin 10  port A To be a RX pin of UART peripheral */
	GPIO_VidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);
	/* Initialize UART peripheral "Enable TX & & RX & peripheral " */
	UART1_voidInit();
	/* Initialize Systick peripheral to be run on 1MHZ Clock */
	SYSTICK_voidInit();
	/* Define an Interval 15 second if this Interval end the CPU will jump to Application Function */
	SYSTICK_voidSetIntervalSingle(15000000,JumpApplicationFunction);
	/* Send Acknowledge to the Master That indicate we are ready to receive the new update of Application Code */
	//UART1_voidTransmitASCI('r');

	while(u8TimeOutFlag == 0)
	{
		/* receive the data which send from master and save it in receiver buffer */
		/* if there is data received data return 1 */
		/* if there is no data received data return 0 */
		Local_u8ReceiverStatus = UART1_u8Receive( &(u8ReceiverBuffer[u8ReceiverCounter]) );
		if (Local_u8ReceiverStatus == 1)
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
				//UART1_voidTransmitASCI('o');
				UART1_voidTransmit("ok");
				/* reset receiver counter to receive the next record */
				u8ReceiverCounter = 0;
			}
			else
			{
				u8ReceiverCounter ++ ;
			}
			/* Define an Interval 15 second if this Interval end the CPU will jump to Application Function */
			SYSTICK_voidSetIntervalSingle(15000000,JumpApplicationFunction);
		}
		else
		{

		}
	}
}
