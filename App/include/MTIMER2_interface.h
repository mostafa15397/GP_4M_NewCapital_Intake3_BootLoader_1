/********************************************************/
/* Author    : Abanoub nader & Mostafa tawfik           */
/* SWC       : TIMER2             				        */
/* Layer     : MCAL                       				*/
/* Version   : 1.0                        				*/
/* Date      : October 16, 2023           				*/
/* Last Edit : N/A                        				*/
/********************************************************/

#ifndef _MTIMER2_INTERFACE_H_
#define _MTIMER2_INTERFACE_H_

/**
 * @brief Starts TIMER2.
 * @note This function starts TIMER2.
 * @return None
 */
void MTIMER2_voidStart(void);

/**
 * @brief Stops TIMER2.
 * @note This function stops TIMER2.
 * @return None
 */
void MTIMER2_voidStop(void);

/**
 * @brief Locks the update event for TIMER2.
 * @note This function locks the update event for TIMER2.
 * @return None
 */
void MTIMER2_voidLockUpdataEvent(void);

/**
 * @brief Unlocks the update event for TIMER2.
 * @note This function unlocks the update event for TIMER2.
 * @return None
 */
void MTIMER2_voidUnlockUpdataEvent(void);

/**
 * @brief Configures TIMER2 for PWM generation.
 * @param ARG_u16TimerPrescalar: The timer prescaler value.
 * @param ARG_u16TimerAutoReload: The timer auto-reload value.
 * @param ARG_u16TimerDutyCycleValue: The duty cycle value for PWM.
 * @note This function configures TIMER2 for PWM generation.
 * @return None
 */
void MTIMER2_voidPWMGeneration(u16 ARG_u16TimerPrescalar, u16 ARG_u16TimerAutoReload, u16 ARG_u16TimerDutyCycleValue);

#endif /* _MTIMER2_INTERFACE_H_ */
