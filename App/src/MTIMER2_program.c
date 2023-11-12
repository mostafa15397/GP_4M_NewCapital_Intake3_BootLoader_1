/********************************************************/
/* Author    : Abanoub nader & Mostafa tawfik           */
/* SWC       : TIMER2             				        */
/* Layer     : MCAL                       				*/
/* Version   : 1.0                        				*/
/* Date      : October 16, 2023           				*/
/* Last Edit : N/A                        				*/
/********************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "MTIMER2_interface.h"
#include "MTIMER2_private.h"
#include "MTIMER2_config.h"
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

/* Private variables ------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */


/**
 * @brief Starts TIMER2.
 * @param None
 * @return None
 */
void MTIMER2_voidStart(void)
{
	SET_BIT(TIMER2->TIMER2_CR1, CR1_CEN);
}

/**
 * @brief Stops TIMER2.
 * @param None
 * @return None
 */
void MTIMER2_voidStop(void)
{
	CLR_BIT(TIMER2->TIMER2_CR1, CR1_CEN);
}

/**
 * @brief Locks the update event for TIMER2.
 * @param None
 * @return None
 */
void MTIMER2_voidLockUpdataEvent(void)
{
	SET_BIT(TIMER2->TIMER2_CR1, CR1_UDIS);
}

/**
 * @brief Unlocks the update event for TIMER2.
 * @param None
 * @return None
 */
void MTIMER2_voidUnlockUpdataEvent(void)
{
	CLR_BIT(TIMER2->TIMER2_CR1, CR1_UDIS);
}

/**
 * @brief Configures TIMER2 for PWM generation.
 * @param ARG_u16TimerPrescalar: The timer prescaler value.
 * @param ARG_u16TimerAutoReload: The timer auto-reload value.
 * @param ARG_u16TimerDutyCycleValue: The duty cycle value for PWM.
 * @return None
 */
void MTIMER2_voidPWMGeneration(u16 ARG_u16TimerPrescalar, u16 ARG_u16TimerAutoReload, u16 ARG_u16TimerDutyCycleValue)
{
	MTIMER2_voidStop();
	TIMER2->TIMER2_PSC = (u32)ARG_u16TimerPrescalar;
	TIMER2->TIMER2_ARR = (u32)ARG_u16TimerAutoReload;
	TIMER2->TIMER2_CCR2 = (u32)ARG_u16TimerDutyCycleValue;
	TIMER2->TIMER2_CCMR1 &= MTIMER2_PWM_MODE_MUSK;
	TIMER2->TIMER2_CCMR1 |= (MTIMER2_MODE_PWM1 << CCMR1_OC2M) | (MTIMER2_OUTCOMPARE_CHANNEL2_ENABLE << CCMR1_OC2PE);
	SET_BIT(TIMER2->TIMER2_CCER, CCER_CC2E);
	SET_BIT(TIMER2->TIMER2_CR1, CR1_ARPE);
	SET_BIT(TIMER2->TIMER2_EGR, EGR_UG);
	MTIMER2_voidStart();
}
