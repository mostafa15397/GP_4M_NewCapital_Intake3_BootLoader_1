/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :UART                        */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 10,2023           */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

#define UART_U8_8_BIT_WORD					0
#define UART_U8_9_BIT_WORD					1

#define UART_U8_PARITY_DISABLED	     		0
#define UART_U8_PARITY_ENABLED				1

#define UART_U8_EVEN_PARITY			    	0
#define UART_U8_ODD_PARITY					1

#define UART_U8_PE_DISABLED			    	0
#define UART_U8_PE_ENABLED					1

void UART1_voidInit(void);
void UART1_voidTransmit(u8 arr[]);
void UART1_voidTransmitASCI(u8 value);
u8   UART1_u8Receive(u8* Copy_u8Data);

#endif
