/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :SYSTICK                     */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 3,2023            */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _SYSTIICK_INTERFACE_H_
#define _SYSTIICK_INTERFACE_H_

/* Apply Clock choice from configuration file 
   Disable SysTick interrupt 
   Disable Systick                          */

void SYSTICK_voidInit(void);
void SYSTICK_voidSetBusyWait( u32 Copy_u32Ticks );
void SYSTICK_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void SYSTICK_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void SYSTICK_voidStopInterval(void);
u32  SYSTICK_u32GetElapsedTime(void);
u32  SYSTICK_u32GetRemainingTime(void);

#endif
