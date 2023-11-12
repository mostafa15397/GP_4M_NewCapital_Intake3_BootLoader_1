/*********************************************************/
/* Author    : Hagar tarek & Panssee mahmoud             */
/* SWC       : FPEC                       			     */
/* Layer     : MCAL                       				 */
/* Version   : 1.0                        				 */
/* Date      : October  8, 2023           				 */
/* Last Edit : N/A                        				 */
/*********************************************************/

#ifndef _FPEC_PRIVATE_H_
#define _FPEC_PRIVATE_H_

typedef union
{
	struct{
		u32  PG    :1 ;
		u32  PER   :1 ;
		u32  MER   :1 ;
		u32  RES1  :1 ;
		u32  OPTPG :1 ;
		u32  OPTER :1 ;
		u32  STRT  :1 ;
		u32  LOCK  :1 ;
		u32  RES2  :1 ;
		u32  OPTWRE:1 ;
		u32  ERRIE :1 ;
		u32  RES3  :1 ;
		u32  EOPIE :1 ;
		u32  RES4  :19;
	}BitAccess;
	u32 WordAccess;
}FPEC_CR_t;

#define FPEC_CR ((FPEC_CR_t*)0x40022010)

typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 AR;
	volatile u32 RESERVED;
	volatile u32 OBR;
	volatile u32 WRPR;
}FPEC_t;

#define FPEC ((FPEC_t*)0x40022000)

#endif
/**
 * @file FPEC_private.h
 * @brief Flash Programming and Erase Controller (FPEC) Private Header File.
 * @author Abanoub Nader
 * @date October 15, 2023
 * @version 1.0
 * 
 * @details
 * This file contains the private definitions and structures for the Flash Programming
 * and Erase Controller (FPEC) driver, including register definitions.
 */

#ifndef _FPEC_PRIVATE_H_
#define _FPEC_PRIVATE_H_

/** @brief FPEC Control Register (FPEC_CR) structure. */
typedef union
{
    struct
    {
        u32  PG    :1 ;  /**< Flash Programming */
        u32  PER   :1 ;  /**< Page Erase */
        u32  MER   :1 ;  /**< Mass Erase */
        u32  RES1  :1 ;  /**< Reserved */
        u32  OPTPG :1 ;  /**< Option Byte Programming */
        u32  OPTER :1 ;  /**< Option Byte Erase */
        u32  STRT  :1 ;  /**< Start */
        u32  LOCK  :1 ;  /**< Lock */
        u32  RES2  :1 ;  /**< Reserved */
        u32  OPTWRE:1 ;  /**< Option Byte Write Enable */
        u32  ERRIE :1 ;  /**< Error Interrupt Enable */
        u32  RES3  :1 ;  /**< Reserved */
        u32  EOPIE :1 ;  /**< End of Operation Interrupt Enable */
        u32  RES4  :19;  /**< Reserved */
    } BitAccess;
    u32 WordAccess;  /**< Access as a 32-bit word. */
} FPEC_CR_t;

#define FPEC_CR ((FPEC_CR_t*)0x40022010)  /**< FPEC Control Register (FPEC_CR) address. */

/** @brief FPEC Register Structure. */
typedef struct
{
    volatile u32 ACR;
    volatile u32 KEYR;
    volatile u32 OPTKEYR;
    volatile u32 SR;
    volatile u32 CR;
    volatile u32 AR;
    volatile u32 RESERVED;
    volatile u32 OBR;
    volatile u32 WRPR;
} FPEC_t;

#define FPEC ((FPEC_t*)0x40022000)  /**< FPEC Register Structure address. */

#endif /* _FPEC_PRIVATE_H_ */
