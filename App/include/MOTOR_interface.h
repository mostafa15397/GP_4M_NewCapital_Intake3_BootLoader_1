/********************************************************/
/* Author    : Abanob nader & Mostafa tawfik            */
/* SWC       : DC MOTOR                   				*/
/* Layer     : HCAL                       				*/
/* Version   : 1.0                        				*/
/* Date      : October 18, 2023           				*/
/* Last Edit : N/A                        				*/
/********************************************************/

#ifndef _MOTOR_INTERFACE_H_
#define _MOTOR_INTERFACE_H_

/**
 * @brief Initializes the DC Motor GPIO pins and Timer configuration.
 */
void MOTOR_voidInti(void);

/**
 * @brief Moves the DC Motor forward.
 */
void MOTOR_voidForward(void);

/**
 * @brief Moves the DC Motor backward.
 */
void MOTOR_voidBackward(void);

/**
 * @brief Turns the DC Motor to the right.
 */
void MOTOR_voidRight(void);

/**
 * @brief Turns the DC Motor to the left.
 */
void MOTOR_voidLeft(void);

/**
 * @brief Stops the DC Motor.
 */
void MOTOR_voidStop(void);

#endif /* _MOTOR_INTERFACE_H_ */
