/*************************************************************/
/* Author    : Abanoub nader & Mohamed mahmoud               */
/* SWC       : GPIO                       					 */
/* Layer     : MCAL                       					 */
/* Version   : 1.0                        					 */
/* Date      : October 15, 2023          					 */
/* Last Edit : N/A                        					 */
/*************************************************************/

#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

#define HIGH    1 /**< High logic level. */
#define LOW     0 /**< Low logic level. */

#define GPIOA   0 /**< GPIO Port A. */
#define GPIOB   1 /**< GPIO Port B. */
#define GPIOC   2 /**< GPIO Port C. */

#define PIN0    0 /**< GPIO Pin 0. */
#define PIN1    1 /**< GPIO Pin 1. */
#define PIN2    2 /**< GPIO Pin 2. */
#define PIN3    3 /**< GPIO Pin 3. */
#define PIN4    4 /**< GPIO Pin 4. */
#define PIN5    5 /**< GPIO Pin 5. */
#define PIN6    6 /**< GPIO Pin 6. */
#define PIN7    7 /**< GPIO Pin 7. */
#define PIN8    8 /**< GPIO Pin 8. */
#define PIN9    9 /**< GPIO Pin 9. */
#define PIN10   10 /**< GPIO Pin 10. */
#define PIN11   11 /**< GPIO Pin 11. */
#define PIN12   12 /**< GPIO Pin 12. */
#define PIN13   13 /**< GPIO Pin 13. */
#define PIN14   14 /**< GPIO Pin 14. */
#define PIN15   15 /**< GPIO Pin 15. */

#define INPUT_ANLOG               0b0000 /**< Analog input mode. */
#define INPUT_FLOATING            0b0100 /**< Floating input mode. */
#define INPUT_PULLUP_PULLDOWN     0b1000 /**< Input with pull-up/pull-down mode. */

// For Speed 10
#define OUTPUT_SPEED_10MHZ_PP     0b0001 /**< Output, push-pull, 10MHz speed. */
#define OUTPUT_SPEED_10MHZ_OD     0b0101 /**< Output, open-drain, 10MHz speed. */
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001 /**< Alternate function, push-pull, 10MHz speed. */
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101 /**< Alternate function, open-drain, 10MHz speed. */

// For Speed 2
#define OUTPUT_SPEED_2MHZ_PP      0b0010 /**< Output, push-pull, 2MHz speed. */
#define OUTPUT_SPEED_2MHZ_OD      0b0110 /**< Output, open-drain, 2MHz speed. */
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010 /**< Alternate function, push-pull, 2MHz speed. */
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110 /**< Alternate function, open-drain, 2MHz speed. */

// For Speed 50
#define OUTPUT_SPEED_50MHZ_PP     0b0011 /**< Output, push-pull, 50MHz speed. */
#define OUTPUT_SPEED_50MHZ_OD     0b0111 /**< Output, open-drain, 50MHz speed. */
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011 /**< Alternate function, push-pull, 50MHz speed. */
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111 /**< Alternate function, open-drain, 50MHz speed. */

/**
 * @brief Set the direction of a GPIO pin.
 * @param Copy_u8Port: GPIO port.
 * @param Copy_u8Pin: GPIO pin.
 * @param u8Copy_u8Mode: Pin mode (e.g., INPUT_FLOATING).
 * @return None.
 */
void GPIO_VidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 u8Copy_u8Mode);

/**
 * @brief Set the value of a GPIO pin.
 * @param Copy_u8Port: GPIO port.
 * @param Copy_u8Pin: GPIO pin.
 * @param u8Copy_u8Value: Pin value (e.g., HIGH or LOW).
 * @return None.
 */
void GPIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 u8Copy_u8Value);

/**
 * @brief Get the value of a GPIO pin.
 * @param Copy_u8Port: GPIO port.
 * @param Copy_u8Pin: GPIO pin.
 * @return The value of the pin (HIGH or LOW).
 */
u8 GPIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);

#endif /* _GPIO_INTERFACE_H_ */
