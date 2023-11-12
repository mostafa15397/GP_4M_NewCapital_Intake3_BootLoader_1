/*********************************************************/
/* Author    : Hagar tarek & Panssee mahmoud             */
/* SWC       : SYSTICK                   			     */
/* Layer     : MCAL                        				 */
/* Version   : 1.0                         				 */
/* Date      : October 17, 2023            				 */
/* Last Edit : N/A                         				 */
/*********************************************************/

#ifndef _SYSTICK_PRIVATE_H_
#define _SYSTICK_PRIVATE_H_

/**
 * @brief Structure representing the SysTick registers.
 */
typedef struct
{
    volatile u32 CTRL;  /**< Control Register. */
    volatile u32 LOAD;  /**< Reload Value Register. */
    volatile u32 VAL;   /**< Current Value Register. */
} STK_t;

/** @brief SysTick base address. */
#define SYSTICK ((STK_t*)0xE000E010)

/** @brief SysTick clock source options. */
#define SYSTICK_SRC_AHB      0  /**< AHB Bus. */
#define SYSTICK_SRC_AHB_8    1  /**< AHB/8 Bus. */

/** @brief SysTick interval mode options. */
#define SYSTICK_SINGLE_INTERVAL    0  /**< Single Interval Mode. */
#define SYSTICK_PERIOD_INTERVAL    1  /**< Periodic Interval Mode. */

#endif

/** @} */
