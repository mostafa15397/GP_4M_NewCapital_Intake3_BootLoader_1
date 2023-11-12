/*********************************************************/
/* Author    : Amir khalifa & Mostafa tawfik             */
/* SWC       : IR Sensor              					 */
/* Layer     : HCAL                     				 */
/* Version   : 1.0                      				 */
/* Date      : October 17, 2023          				 */
/* Last Edit : N/A                      				 */
/*********************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_INTERFACE.h"

#include "IR_SENSOR_config.h"
#include "IR_SENSOR_interface.h"
#include "IR_SENSOR_private.h"
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

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
 * @brief Initializes the IR Sensor GPIO pins.
 * @param None
 * @note This function configures the GPIO pins connected to the IR sensor as floating inputs.
 * @return None
 */
void IR_SENSOR_voidInti(void)
{	
    GPIO_VidSetPinDirection(IR_SENSOR_PORT, IR_SENSOR_RIGHT_PIN, INPUT_FLOATING);
    GPIO_VidSetPinDirection(IR_SENSOR_PORT, IR_SENSOR_LEFT_PIN, INPUT_FLOATING);
}

/**
 * @brief Reads the right IR sensor.
 * @param None
 * @note This function reads the digital value of the right IR sensor pin.
 * @retval u8: Digital value (0 or 1) indicating the IR sensor reading.
 */
u8 IR_SENSOR_u8GetRightReading(void)
{
    u8 Local_u8ReadingValue = 0;
    Local_u8ReadingValue = GPIO_u8GetPinValue(IR_SENSOR_PORT, IR_SENSOR_RIGHT_PIN);
    return Local_u8ReadingValue;
}

/**
 * @brief Reads the left IR sensor.
 * @param None
 * @note This function reads the digital value of the left IR sensor pin.
 * @retval u8: Digital value (0 or 1) indicating the IR sensor reading.
 */
u8 IR_SENSOR_u8GetLeftReading(void)
{
    u8 Local_u8ReadingValue = 0;
    Local_u8ReadingValue = GPIO_u8GetPinValue(IR_SENSOR_PORT, IR_SENSOR_LEFT_PIN);
    return Local_u8ReadingValue;
}
