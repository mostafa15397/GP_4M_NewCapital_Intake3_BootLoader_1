/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :UART1                        */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 10,2023           */
/*Last Edit :N/A                         */
/*****************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"

void UART1_voidInit(void)
{
	/*	baud rate = 9600		*/
	UART1 -> BRR = 0x341;
	SETBIT((UART1-> CR[0]), 3);			/* Enabling Transmitter */
	SETBIT((UART1-> CR[0]), 2);			/* Enabling Receiver */
	SETBIT((UART1-> CR[0]), 13);			/* Enabling USART */
	UART1 -> SR = 0;						/* Clearing status register */
}

void UART1_voidTransmit(u8 copy_u8Data[])
{
	u8 Local_u8DataCounter = 0;
	while(copy_u8Data[Local_u8DataCounter] != '\0')
	{
		/* put data in sender buffer */
		UART1 -> DR = copy_u8Data[Local_u8DataCounter];
		/* wait till complete send to be set */
		while((GET_BIT((UART1 -> SR), 6)) == 0);
		/* take next element of data */
		Local_u8DataCounter++;
	}
}

void UART1_voidTransmitASCI(u8 value)
{
	/* put data in sender buffer */
	UART1 -> DR = value;
	/* wait till complete send to be set */
	while((GET_BIT((UART1 -> SR), 6)) == 0);
}

u8 UART1_u8Receive(u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;
	/* ask if there is a received data take it and return 1 */
	/* or return 0 if there is no data reveived */
	if ( (GET_BIT((UART1 -> SR), 5)) == 1 )
	{
		*Copy_u8Data = UART1 -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}
	return (Local_u8Result);
}
