/********************************************************/
/* Author    : Abanob nader & Mostafa tawfik            */
/* SWC       : DC MOTOR                   				*/
/* Layer     : HCAL                       				*/
/* Version   : 1.0                        				*/
/* Date      : October 18, 2023           				*/
/* Last Edit : N/A                        				*/
/********************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GPIO_INTERFACE.h"
#include "MTIMER2_interface.h"
#include "AFIO_interface.h"

#include "MOTOR_config.h"
#include "MOTOR_interface.h"
#include "MOTOR_private.h"
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
 * @brief Initializes the DC Motor GPIO pins and Timer configuration .
 * @param None
 * @note   This function intialize 4 pins to be output with 2 MHZ speed and confige Timer2 in Normal Remapped using AFIO driver.
 * @return None
 */
void MOTOR_voidInti(void)
{	
	GPIO_VidSetPinDirection(MOTOR_PORT, MOTOR_RIGHT1_PIN, OUTPUT_SPEED_2MHZ_PP);
	GPIO_VidSetPinDirection(MOTOR_PORT, MOTOR_RIGHT2_PIN, OUTPUT_SPEED_2MHZ_PP);
	GPIO_VidSetPinDirection(MOTOR_PORT, MOTOR_LEFT1_PIN, OUTPUT_SPEED_2MHZ_PP);
	GPIO_VidSetPinDirection(MOTOR_PORT, MOTOR_LEFT2_PIN, OUTPUT_SPEED_2MHZ_PP);
	GPIO_VidSetPinDirection(MOTOR_PORT, MOTOR_ENABLE_R_L_PIN, OUTPUT_SPEED_2MHZ_AFPP);
	
	AFIO_viodSetTimer2Configuration(TIMER2_NOREMAPPED);
} 

/**
 * @brief Moves the DC Motor forward.
 * @param None
 * @note   This function SET 2 pin to be High volte and 2 with low volte and confige Timer2 PWM  with 1000 MOTOR_AUTOLOAD ,MOTOR_PRESCALAR =1 , 50% Dutycycle .
 * @return None
 */
void MOTOR_voidForward(void)
{
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT1_PIN, HIGH);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT2_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT1_PIN, HIGH);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT2_PIN, LOW);

	MTIMER2_voidPWMGeneration(MOTOR_PRESCALAR, MOTOR_AUTOLOAD, MOTOR_DUTYCYCLE_FORWARD);
} 

/**
 * @brief Moves the DC Motor backward.
 * @param None
 * @note   This function SET 2 pin to be High volte and 2 with low volte and confige Timer2 PWM  with 1000 MOTOR_AUTOLOAD ,MOTOR_PRESCALAR =1 , 50% Dutycycle .
 * @return None
 */
void MOTOR_voidBackward(void)
{
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT2_PIN, HIGH);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT2_PIN, HIGH);

	MTIMER2_voidPWMGeneration(MOTOR_PRESCALAR, MOTOR_AUTOLOAD, MOTOR_DUTYCYCLE_FORWARD);
}

/**
 * @brief Turns the DC Motor to the right.
 * @param None
 * @note   This function SET 1 pin to be High volte and 3 with low volte and confige Timer2 PWM  with 1000 MOTOR_AUTOLOAD ,MOTOR_PRESCALAR =1 , 50% Dutycycle .
 * @return None
 */
void MOTOR_voidRight(void)
{
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT2_PIN, HIGH);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT2_PIN, LOW);

	MTIMER2_voidPWMGeneration(MOTOR_PRESCALAR, MOTOR_AUTOLOAD, MOTOR_DUTYCYCLE_TURN);
} 

/**
 * @brief Turns the DC Motor to the left.
 * @param None
 * @note   This function SET 1 pin to be High volte and 3 with low volte and confige Timer2 PWM  with 1000 MOTOR_AUTOLOAD ,MOTOR_PRESCALAR =1 , 50% Dutycycle .
 * @return None
 */
void MOTOR_voidLeft(void)
{
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT2_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT2_PIN, HIGH);

	MTIMER2_voidPWMGeneration(MOTOR_PRESCALAR, MOTOR_AUTOLOAD, MOTOR_DUTYCYCLE_TURN);
}  

/**
 * @brief Stops the DC Motor.
 * @param None
 * @note   This function SET 4 pin to low volte and confige Timer2 PWM  with 1000 MOTOR_AUTOLOAD ,MOTOR_PRESCALAR =1 , 50% Dutycycle .
 * @return None
 */
void MOTOR_voidStop(void)
{
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_RIGHT2_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT1_PIN, LOW);
	GPIO_VidSetPinValue(MOTOR_PORT, MOTOR_LEFT2_PIN, LOW);

	MTIMER2_voidPWMGeneration(MOTOR_PRESCALAR, MOTOR_AUTOLOAD, MOTOR_DUTYCYCLE_FORWARD);
}
