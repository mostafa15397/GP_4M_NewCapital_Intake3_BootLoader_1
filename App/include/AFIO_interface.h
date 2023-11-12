#ifndef _AFIO_INTERFACE_H_
#define _AFIO_INTERFACE_H_

/** EXTI Line Constants */
#define EXTI0  0   /**< EXTI Line 0 */
#define EXTI1  1   /**< EXTI Line 1 */
#define EXTI2  2   /**< EXTI Line 2 */
#define EXTI3  3   /**< EXTI Line 3 */
#define EXTI4  4   /**< EXTI Line 4 */
#define EXTI5  5   /**< EXTI Line 5 */
#define EXTI6  6   /**< EXTI Line 6 */
#define EXTI7  7   /**< EXTI Line 7 */
#define EXTI8  8   /**< EXTI Line 8 */
#define EXTI9  9   /**< EXTI Line 9 */
#define EXTI10 10  /**< EXTI Line 10 */
#define EXTI11 11  /**< EXTI Line 11 */
#define EXTI12 12  /**< EXTI Line 12 */
#define EXTI13 13  /**< EXTI Line 13 */
#define EXTI14 14  /**< EXTI Line 14 */
#define EXTI15 15  /**< EXTI Line 15 */

/** Timer2 Remapping Options */
#define TIMER2_NOREMAPPED          0   /**< Timer2 Not Remapped */
#define TIMER2_PARTIALREMAPPED_1   1   /**< Timer2 Partial Remapped Option 1 */
#define TIMER2_PARTIALREMAPPED_2   2   /**< Timer2 Partial Remapped Option 2 */
#define TIMER2_FULLYREMAPPED       3   /**< Timer2 Fully Remapped */

/**
 * @brief Configures the EXTI line for a specific pin.
 * @param LOC_u8EXTI_Line EXTI line number (0 to 15).
 * @param LOC_u8PortMap Port source mapping for EXTI (0 to 0xF).
 * @note This function configures the EXTI line for a specific pin based on the EXTI line number and port mapping.
 */
void AFIO_ViodSetEXTIConfiguration( u8 LOC_u8EXTI_Line , u8 LOC_u8PortMap );

/**
 * @brief Configures the remapping of Timer2.
 * @param LOC_u8Timer2Map Timer2 remapping option.
 *        - TIMER2_NOREMAPPED: No remapping.
 *        - TIMER2_PARTIALREMAPPED_1: Partial remapping option 1.
 *        - TIMER2_PARTIALREMAPPED_2: Partial remapping option 2.
 *        - TIMER2_FULLYREMAPPED: Fully remapped.
 * @note This function configures the remapping of Timer2 based on the selected option.
 */
void AFIO_viodSetTimer2Configuration(u8 LOC_u8Timer2Map);

#endif /* _AFIO_INTERFACE_H_ */

/** @} */
