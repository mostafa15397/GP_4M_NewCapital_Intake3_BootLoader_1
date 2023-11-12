/************************************************************/
/* Author    : Mostafa tawfik & Panssee mahmoud             */
/* SWC       : UART1                      					*/
/* Layer     : MCAL                       					*/
/* Version   : 1.0                        					*/
/* Date      : October 14, 2023         					*/
/* Last Edit : N/A                        					*/
/************************************************************/

#ifndef _UART1_PRIVATE_H_
#define _UART1_PRIVATE_H_

/**
 * @brief Structure representing the UART1 registers.
 */
typedef struct {
    volatile u32 SR;       /**< Status register. */
    volatile u32 DR;       /**< Data register. */
    volatile u32 BRR;      /**< Baud rate register. */
    volatile u32 CR[3];    /**< Control registers 1, 2, and 3. */
    volatile u32 GTPR;     /**< Guard time and prescaler register. */
} UART_t;

/** @brief UART1 Base Address. */
#define UART1       ((UART_t *)0x40013800)

/** @} */

#endif /* _UART1_PRIVATE_H_ */
