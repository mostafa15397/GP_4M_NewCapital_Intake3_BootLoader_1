/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :UART                        */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 10,2023           */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _UART1_PRIVATE_H_
#define _UART1_PRIVATE_H_

typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR[3];
	volatile u32 GTPR;
}UART_t;

#define 	UART1 		((UART_t *) 0x40013800)

#endif
