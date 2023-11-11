/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :SYSTICK                     */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 3,2023            */
/*Last Edit :N/A                         */
/*****************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_config.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"

/* Define Callback Global Variable */
static void(*SYSTICK_CallBack)(void);

/* Define Variable for interval mode */
static u8 u8ModeOfInterval;

void SYSTICK_voidInit(void)
{
#if SYSTICK_CLK_SRC == SYSTICK_SRC_AHB
    /* Disable STK - Disable STK Interrupt - Set clock source AHB */
	SYSTICK -> CTRL = 0x00000004;
#else
    /* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
	SYSTICK -> CTRL = 0;
#endif
}

void SYSTICK_voidSetBusyWait( u32 Copy_u32Ticks )
{
	/* Load ticks to load register */
	SYSTICK -> LOAD = Copy_u32Ticks;
	/* Start Timer */
	SETBIT(SYSTICK->CTRL, 0);
	/* Wait till flag is raised */
	while( (GET_BIT(SYSTICK->CTRL,16)) == 0);
	/* Stop Timer */
	CLR_BIT(SYSTICK->CTRL, 0);
	SYSTICK -> LOAD = 0;
	SYSTICK -> VAL  = 0;
}

void SYSTICK_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/* Stop Timer */
	CLR_BIT(SYSTICK->CTRL, 0);
	SYSTICK -> LOAD = 0;
	SYSTICK -> VAL  = 0;
	/* Load ticks to load register */
	SYSTICK -> LOAD = Copy_u32Ticks;
	/* Start Timer */
	SETBIT(SYSTICK->CTRL, 0);
	/* Save CallBack */
	SYSTICK_CallBack = Copy_ptr;
	/* Set Mode to Single */
	u8ModeOfInterval = SYSTICK_SINGLE_INTERVAL;
	/* Enable STK Interrupt */
	SETBIT(SYSTICK->CTRL, 1);
}

void SYSTICK_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/* Load ticks to load register */
	SYSTICK -> LOAD = Copy_u32Ticks;
	/* Start Timer */
	SETBIT(SYSTICK->CTRL, 0);
	/* Save CallBack */
	SYSTICK_CallBack = Copy_ptr;
	/* Set Mode to Single */
	u8ModeOfInterval = SYSTICK_PERIOD_INTERVAL;
	/* Enable STK Interrupt */
	SETBIT(SYSTICK->CTRL, 1);
}

void SYSTICK_voidStopInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(SYSTICK->CTRL, 1);
	/* Stop Timer */
	SETBIT(SYSTICK->CTRL, 0);
	SYSTICK -> LOAD = 0;
	SYSTICK -> VAL  = 0;
}

u32  SYSTICK_u32GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	Local_u32ElapsedTime = (SYSTICK -> LOAD) - (SYSTICK -> VAL) ;
	return Local_u32ElapsedTime;
}

u32  SYSTICK_u32GetRemainingTime(void)
{
	u32 Local_u32RemainTime;
	Local_u32RemainTime = SYSTICK -> VAL ;
	return Local_u32RemainTime;
}

