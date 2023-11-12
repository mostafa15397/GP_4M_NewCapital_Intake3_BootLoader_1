/*************************************************************/
/* Author    : Abanoub nader & Mohamed mahmoud               */
/* SWC       : GPIO                       					 */
/* Layer     : MCAL                       					 */
/* Version   : 1.0                        					 */
/* Date      : October 15, 2023          					 */
/* Last Edit : N/A                        					 */
/*************************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
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
  * @brief  Set the direction of a specific pin in a GPIO port.
  * @param  Copy_u8Port: GPIO port (DIOA, DIOB, or DIOC)
  * @param  Copy_u8Pin:  Pin number (0 to 15)
  * @param  u8Copy_u8Mode: Pin mode (INPUT, OUTPUT, etc.)
  * @return None
  */
void GPIO_VidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 u8Copy_u8Mode)
{
    switch (Copy_u8Port)
    {
    case DIOA:
        if (Copy_u8Pin <= 7)
        {
            // Configure low pins
            GPIOA_CRL &= ~((0b1111) << (Copy_u8Pin * 4)); // Read-Modify-Write
            GPIOA_CRL |= (u8Copy_u8Mode) << (Copy_u8Pin * 4);
        }
        else if (Copy_u8Pin <= 15)
        {
            // Configure high pins
            Copy_u8Pin = Copy_u8Pin - 8;
            GPIOA_CRH &= ~((0b1111) << (Copy_u8Pin * 4));
            GPIOA_CRH |= (u8Copy_u8Mode) << (Copy_u8Pin * 4);
        }
        break;
    case DIOB:
        if (Copy_u8Pin <= 7)
        {
            // Configure low pins
            GPIOB_CRL &= ~((0b1111) << (Copy_u8Pin * 4)); // Read-Modify-Write
            GPIOB_CRL |= (u8Copy_u8Mode) << (Copy_u8Pin * 4);
        }
        else if (Copy_u8Pin <= 15)
        {
            // Configure high pins
            Copy_u8Pin = Copy_u8Pin - 8;
            GPIOB_CRH &= ~((0b1111) << (Copy_u8Pin * 4));
            GPIOB_CRH |= (u8Copy_u8Mode) << (Copy_u8Pin * 4);
        }
        break;
    case DIOC:
        if (Copy_u8Pin <= 7)
        {
            // Configure low pins
            GPIOC_CRL &= ~((0b1111) << (Copy_u8Pin * 4)); // Read-Modify-Write
            GPIOC_CRL |= (u8Copy_u8Mode) << (Copy_u8Pin * 4);
        }
        else if (Copy_u8Pin <= 15)
        {
            // Configure high pins
            Copy_u8Pin = Copy_u8Pin - 8;
            GPIOC_CRH &= ~((0b1111) << (Copy_u8Pin * 4));
            GPIOC_CRH |= (u8Copy_u8Mode) << (Copy_u8Pin * 4);
        }
        break;
    default:
        break;
    }
}

/**
  * @brief  Set the value of a specific pin in a GPIO port.
  * @param  Copy_u8Port: GPIO port (DIOA, DIOB, or DIOC)
  * @param  Copy_u8Pin:  Pin number (0 to 15)
  * @param  u8Copy_u8Value: Pin value (HIGH or LOW)
  * @return None
  */
void GPIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 u8Copy_u8Value)
{
    switch (Copy_u8Port)
    {
    case DIOA:
        if (u8Copy_u8Value == HIGH)
        {
            SETBIT(GPIOA_ODR, Copy_u8Pin);
        }
        else if (u8Copy_u8Value == LOW)
        {
            CLR_BIT(GPIOA_ODR, Copy_u8Pin);
        }
        break;
    case DIOB:
        if (u8Copy_u8Value == HIGH)
        {
            SETBIT(GPIOB_ODR, Copy_u8Pin);
        }
        else if (u8Copy_u8Value == LOW)
        {
            CLR_BIT(GPIOB_ODR, Copy_u8Pin);
        }
        break;
    case DIOC:
        if (u8Copy_u8Value == HIGH)
        {
            SETBIT(GPIOC_ODR, Copy_u8Pin);
        }
        else if (u8Copy_u8Value == LOW)
        {
            CLR_BIT(GPIOC_ODR, Copy_u8Pin);
        }
        break;
    }
}

/**
  * @brief  Get the value of a specific pin in a GPIO port.
  * @param  Copy_u8Port: GPIO port (DIOA, DIOB, or DIOC)
  * @param  Copy_u8Pin:  Pin number (0 to 15)
  * @retval The value of the specified pin (1 or 0)
  */
u8 GPIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    u8 Local_u8Result = 0;
    switch (Copy_u8Port)
    {
    case DIOA:
        Local_u8Result = GET_BIT(GPIOA_IDR, Copy_u8Pin);
        break;
    case DIOB:
        Local_u8Result = GET_BIT(GPIOB_IDR, Copy_u8Pin);
        break;
    case DIOC:
        Local_u8Result = GET_BIT(GPIOC_IDR, Copy_u8Pin);
        break;
    }
    return Local_u8Result;
}
