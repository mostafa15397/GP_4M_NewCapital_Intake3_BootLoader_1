/********************************************************/
/* Author    : Abanob nader & Mostafa tawfik            */
/* SWC       : DC MOTOR                   				*/
/* Layer     : HCAL                       				*/
/* Version   : 1.0                        				*/
/* Date      : October 18, 2023           				*/
/* Last Edit : N/A                        				*/
/********************************************************/

#ifndef   _MOTOR_CONFIG_H_
#define   _MOTOR_CONFIG_H_

#define    MOTOR_PORT              GPIOA

#define    MOTOR_RIGHT1_PIN        PIN0
#define    MOTOR_RIGHT2_PIN        PIN2
#define    MOTOR_LEFT1_PIN         PIN3
#define    MOTOR_LEFT2_PIN         PIN4
#define    MOTOR_ENABLE_R_L_PIN    PIN1

#define    MOTOR_PRESCALAR           0
#define    MOTOR_AUTOLOAD            60000
#define    MOTOR_DUTYCYCLE_FORWARD   15000
#define    MOTOR_DUTYCYCLE_TURN      9000

#endif
