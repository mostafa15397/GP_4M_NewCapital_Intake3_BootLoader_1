/*******************************************************/
/* Author    : Amir khalifa & Mohamed mahmoud          */
/* SWC       : RCC                        			   */
/* Layer     : MCAL                         		   */
/* Version   : 1.0                        			   */
/* Date      : October 16, 2023            			   */
/* Last Edit : N/A                        			   */
/*******************************************************/

#ifndef _RCC_INTERFACE_H_
#define _RCC_INTERFACE_H_

/**
 * @defgroup RCC RCC Module
 * @{
 */

/**
 * @brief Bus identifiers for enable/disable clock functions.
 */
#define RCC_AHB       0   /**< AHB Bus */
#define RCC_APB1      1   /**< APB1 Bus */
#define RCC_APB2      2   /**< APB2 Bus */

/**
 * @brief Peripheral identifiers for enable/disable clock functions.
 */
#define RCC_UART1     14  /**< UART1 Peripheral */
#define RCC_GPIOA     2   /**< GPIOA Peripheral */
#define RCC_FPEC      4   /**< Flash Peripheral */

/**
 * @brief Initializes the system clock based on the selected configuration.
 * @note This function configures the system clock based on the selected clock type
 *       and options in the RCC_config.h file.
 * @return None
 */
void RCC_voidInitSysClock(void);

/**
 * @brief Enables the clock for a specific peripheral on the specified bus.
 * @param Copy_u8BusId: Bus ID (RCC_AHB, RCC_APB1, RCC_APB2).
 * @param Copy_u8PerId: Peripheral ID (0 to 31).
 * @note This function enables the clock for the specified peripheral on the selected bus.
 * @return None
 */
void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);

/**
 * @brief Disables the clock for a specific peripheral on the specified bus.
 * @param Copy_u8BusId: Bus ID (RCC_AHB, RCC_APB1, RCC_APB2).
 * @param Copy_u8PerId: Peripheral ID (0 to 31).
 * @note This function disables the clock for the specified peripheral on the selected bus.
 * @return None
 */
void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);

/** @} */

#endif
