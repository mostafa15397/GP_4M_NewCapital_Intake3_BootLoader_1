/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :RCC                         */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :August 30,2023              */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _RCC_INTERFACE_H_
#define _RCC_INTERFACE_H_

#define RCC_AHB       0 
#define RCC_APB1      1
#define RCC_APB2      2

#define RCC_UART1     14
#define RCC_GPIOA     2
#define RCC_FPEC      4

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);

#endif
