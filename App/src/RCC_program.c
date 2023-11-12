/*******************************************************/
/* Author    : Amir khalifa & Mohamed mahmoud          */
/* SWC       : RCC                        			   */
/* Layer     : MCAL                         		   */
/* Version   : 1.0                        			   */
/* Date      : October 16, 2023            			   */
/* Last Edit : N/A                        			   */
/*******************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
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
  * @brief  Initialize the system clock based on the selected configuration.
  * @note   This function configures the system clock based on the selected clock type
  *         and options in the RCC_config.h file.
  * @param  None
  * @return None
  */
void RCC_voidInitSysClock(void)
{
	#if RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		/* Enable HSE with no bypass */
		RCC_CR   = 0x00010000;
		/* Configure system clock to use HSE */
		RCC_CFGR = 0x00000001;

	#elif RCC_CLOCK_TYPE == RCC_HSE_RC
		/* Enable HSE with bypass */
		RCC_CR   = 0x00050000;
		/* Configure system clock to use HSE */
		RCC_CFGR = 0x00000001;

	#elif RCC_CLOCK_TYPE == RCC_HSI
		/* Enable HSI with Trimming = 0 */
		RCC_CR   = 0x00000081;
		/* Configure system clock to use HSI */
		RCC_CFGR = 0x00000000;

	#elif RCC_CLOCK_TYPE == RCC_PLL
		#if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			/* PLL configuration for HSI/2 input */
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
			/* PLL configuration for HSE/2 input */
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
			/* PLL configuration for HSE input */
		#endif

	#else
		#error("You chose the wrong clock type")
	#endif
}

/**
  * @brief  Enable the clock for a specific peripheral on the specified bus.
  * @param  Copy_u8BusId: Bus ID (RCC_AHB, RCC_APB1, RCC_APB2)
  * @param  Copy_u8PerId: Peripheral ID (0 to 31)
  * @note   This function enables the clock for the specified peripheral on the
  *         selected bus.
  * @return None
  */
void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31)
	{
		switch (Copy_u8BusId)
		{
			case RCC_AHB  : SETBIT(RCC_AHBENR  , Copy_u8PerId);   break;
			case RCC_APB1 : SETBIT(RCC_APB1ENR , Copy_u8PerId);   break;
			case RCC_APB2 : SETBIT(RCC_APB2ENR , Copy_u8PerId);   break;
		}
	}
	else
	{
		/* Return Error */
	}
}

/**
  * @brief  Disable the clock for a specific peripheral on the specified bus.
  * @param  Copy_u8BusId: Bus ID (RCC_AHB, RCC_APB1, RCC_APB2)
  * @param  Copy_u8PerId: Peripheral ID (0 to 31)
  * @note   This function disables the clock for the specified peripheral on the
  *         selected bus.
  * @return None
  */
void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31)
	{
		switch (Copy_u8BusId)
		{
			case RCC_AHB  : CLR_BIT(RCC_AHBENR  , Copy_u8PerId);   break;
			case RCC_APB1 : CLR_BIT(RCC_APB1ENR , Copy_u8PerId);   break;
			case RCC_APB2 : CLR_BIT(RCC_APB2ENR , Copy_u8PerId);   break;
		}
	}
	else
	{
		/* Return Error */
	}
}
