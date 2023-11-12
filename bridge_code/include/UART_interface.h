/************************************************************/
/* Author    : Mostafa tawfik & Panssee mahmoud             */
/* SWC       : UART1                      					*/
/* Layer     : MCAL                       					*/
/* Version   : 1.0                        					*/
/* Date      : October 14, 2023         					*/
/* Last Edit : N/A                        					*/
/************************************************************/

#ifndef _UART1_INTERFACE_H_
#define _UART1_INTERFACE_H_

/**
 * @brief Word Length options for UART1.
 */
#define UART1_U8_8_BIT_WORD         0 /**< 8-bit word length. */
#define UART1_U8_9_BIT_WORD         1 /**< 9-bit word length. */

/**
 * @brief Parity options for UART1.
 */
#define UART1_U8_PARITY_DISABLED    0 /**< Parity disabled. */
#define UART1_U8_PARITY_ENABLED     1 /**< Parity enabled. */

/**
 * @brief Parity type options for UART1.
 */
#define UART1_U8_EVEN_PARITY        0 /**< Even parity. */
#define UART1_U8_ODD_PARITY         1 /**< Odd parity. */

/**
 * @brief Parity Error options for UART1.
 */
#define UART1_U8_PE_DISABLED        0 /**< Parity error checking disabled. */
#define UART1_U8_PE_ENABLED         1 /**< Parity error checking enabled. */

/**
 * @brief Initialize UART1 with default settings.
 * @note This function configures UART1 with default settings.
 * @return None
 */
void UART1_voidInit(void);

/**
 * @brief Transmit a string of data using UART1.
 * @param arr: The string to be transmitted.
 * @note This function transmits a string of data using UART1.
 *       It waits for each character to be sent and then proceeds to the next one.
 * @return None
 */
void UART1_voidTransmit(u8 arr[]);

/**
 * @brief Transmit a single ASCII character using UART1.
 * @param value: The ASCII character to be transmitted.
 * @note This function transmits a single ASCII character using UART1.
 *       It waits for the transmission to complete before returning.
 * @return None
 */
void UART1_voidTransmitASCI(u8 value);

/**
 * @brief Receive a character using UART1.
 * @param Copy_u8Data: Pointer to the variable where the received data will be stored.
 * @return 1 if data is received, 0 if no data is received.
 */
u8 UART1_u8Receive(u8* Copy_u8Data);

/** @} */

#endif /* _UART1_INTERFACE_H_ */

