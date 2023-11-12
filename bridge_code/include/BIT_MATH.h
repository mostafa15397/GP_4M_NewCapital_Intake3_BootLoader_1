/**
 * @file BIT_MATH.h
 * @brief Bit Manipulation Macros Header File.
 * @author Abanoub Nader
 * @date August 25, 2023
 * @version 1.0
 * 
 * @details
 * This file contains macros for common bit manipulation operations.
 */

#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

/**
 * @brief Set a specific bit in a variable.
 * @param VAR The variable to set the bit in.
 * @param BIT The bit position to set.
 */
#define SET_BIT(VAR, BIT)          VAR |=  (1 << (BIT))

/**
 * @brief Clear a specific bit in a variable.
 * @param VAR The variable to clear the bit in.
 * @param BIT The bit position to clear.
 */
#define CLR_BIT(VAR, BIT)          VAR &= ~(1 << (BIT))

/**
 * @brief Get the value of a specific bit in a variable.
 * @param VAR The variable to get the bit value from.
 * @param BIT The bit position to get.
 * @return The value of the specified bit (0 or 1).
 */
#define GET_BIT(VAR, BIT)          ((VAR >> BIT) & 1)

/**
 * @brief Toggle a specific bit in a variable.
 * @param VAR The variable to toggle the bit in.
 * @param BIT The bit position to toggle.
 */
#define TOG_BIT(VAR, BIT)          VAR ^=  (1 << (BIT))

#endif /* _BIT_MATH_H_ */