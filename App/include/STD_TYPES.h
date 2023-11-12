/*****************************************/
/* Author    : Abanob Nader              */
/* SWC       : BIT MATH                  */
/* Layer     : LIB                       */
/* Version   : 1.0                       */
/* Date      : August 25, 2023           */
/* Last Edit : N/A                       */
/*****************************************/

/**
 * @file STD_TYPES.h
 * @brief Standard Types Header File.
 * @author Abanob Nader
 * @date August 25, 2023
 * @version 1.0
 * @defgroup STD_TYPES Standard Types
 * @{
 */

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

/**
 * @brief Definition of unsigned 8-bit integer type.
 */
typedef unsigned char        u8 ;

/**
 * @brief Definition of unsigned 16-bit integer type.
 */
typedef unsigned short int   u16;

/**
 * @brief Definition of unsigned 32-bit integer type.
 */
typedef unsigned long  int   u32; 

/**
 * @brief Definition of signed 8-bit integer type.
 */
typedef signed char        s8 ;

/**
 * @brief Definition of signed 16-bit integer type.
 */
typedef signed short int   s16;

/**
 * @brief Definition of signed 32-bit integer type.
 */
typedef signed long  int   s32; 

/**
 * @brief Definition of unsigned 64-bit integer type.
 */
typedef unsigned long long int u64 ;

/**
 * @brief Definition of signed 64-bit integer type.
 */
typedef signed long long int   s64 ;

/**
 * @brief Definition of 32-bit floating-point type.
 */
typedef float  f32;

/**
 * @brief Definition of 64-bit floating-point type.
 */
typedef double f64;

/**
 * @brief Enumeration for common error statuses.
 */
typedef enum{
    OK,             /**< Operation successful. */
    NOK,            /**< Operation not successful. */
    OUT_OF_RANGE,   /**< Value out of range. */
    NULL_POINTER    /**< Null pointer encountered. */
} ErrorStatus;

#endif

/** @} */
