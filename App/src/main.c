/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "SYSTICK_interface.h"
#include "IR_SENSOR_interface.h"
#include "MOTOR_interface.h"
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
 * @brief Application entry point.
 * @retval int
 */
int main(void)
{
    /* MCU Configuration -------------------------------------------------------*/
    /* Reset of all peripherals, Initializes the Flash interface, and the Systick. */
    RCC_voidInitSysClock();                                  // Initialize the system clock.
    RCC_voidEnableClock(RCC_APB2, RCC_AFIO);                 // Enable Alternative Function peripheral clock.
    RCC_voidEnableClock(RCC_APB2, RCC_GPIOA);                // Enable GPIOA clock.
    RCC_voidEnableClock(RCC_APB1, RCC_TIM2);                // Enable Timer2 clock.

    /* Initialize Systick peripheral to run on a 1MHz Clock */
    SYSTICK_voidInit();

    /* Initialize GPIO Pins to which IR Sensors are connected as input Floating to get readings for the sensors */
    IR_SENSOR_voidInti();

    /* Initialize GPIO Pins to which Motors are connected as output push-pull to control motor behavior */
    MOTOR_voidInti();

    while (1)
    {
        /* Check IR Sensor readings to make decisions for motor control */
        /* If both right and left sensors return low, it means both sensors read white, so the motors move forward. */
        /* If one of them returns high, it means one sensor read a black line, so the motors turn right or left according to which sensor read the black line. */
        /* If both right and left sensors return high, it means both sensors read a black line, so the motors stop. */
        if ((IR_SENSOR_u8GetRightReading() == 0) && (IR_SENSOR_u8GetLeftReading() == 0))
        {
            MOTOR_voidForward();
        }
        else if ((IR_SENSOR_u8GetRightReading() == 0) && (IR_SENSOR_u8GetLeftReading() == 1))
        {
            MOTOR_voidLeft();
        }
        else if ((IR_SENSOR_u8GetRightReading() == 1) && (IR_SENSOR_u8GetLeftReading() == 0))
        {
            MOTOR_voidRight();
        }
        else if ((IR_SENSOR_u8GetRightReading() == 1) && (IR_SENSOR_u8GetLeftReading() == 1))
        {
            MOTOR_voidStop();
        }

        SYSTICK_voidSetBusyWait(25000);  // Delay to control the rate of sensor readings and motor control.
    }

    return 0;
}
