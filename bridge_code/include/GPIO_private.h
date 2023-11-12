/*************************************************************/
/* Author    : Abanoub nader & Mohamed mahmoud               */
/* SWC       : GPIO                       					 */
/* Layer     : MCAL                       					 */
/* Version   : 1.0                        					 */
/* Date      : October 15, 2023          					 */
/* Last Edit : N/A                        					 */
/*************************************************************/

#ifndef _GPIO_PRIVATE_H_
#define _GPIO_PRIVATE_H_

#define GPIOA_Base_Address        0x40010800 /**< Base address of GPIO Port A. */
#define GPIOB_Base_Address        0x40010C00 /**< Base address of GPIO Port B. */
#define GPIOC_Base_Address        0x40011000 /**< Base address of GPIO Port C. */

/* REGISTERS ADDRESSES FOR Port A */
#define GPIOA_CRL                 *((u32*)(GPIOA_Base_Address + 0x00)) /**< GPIO Port A Configuration Register Low. */
#define GPIOA_CRH                 *((u32*)(GPIOA_Base_Address + 0x04)) /**< GPIO Port A Configuration Register High. */
#define GPIOA_IDR                 *((u32*)(GPIOA_Base_Address + 0x08)) /**< GPIO Port A Input Data Register. */
#define GPIOA_ODR                 *((u32*)(GPIOA_Base_Address + 0x0C)) /**< GPIO Port A Output Data Register. */
#define GPIOA_BSR                 *((u32*)(GPIOA_Base_Address + 0x10)) /**< GPIO Port A Bit Set Register. */
#define GPIOA_BRR                 *((u32*)(GPIOA_Base_Address + 0x14)) /**< GPIO Port A Bit Reset Register. */
#define GPIOA_LCK                 *((u32*)(GPIOA_Base_Address + 0x18)) /**< GPIO Port A Lock Register. */

/* REGISTERS ADDRESSES FOR Port B */
#define GPIOB_CRL                 *((u32*)(GPIOB_Base_Address + 0x00)) /**< GPIO Port B Configuration Register Low. */
#define GPIOB_CRH                 *((u32*)(GPIOB_Base_Address + 0x04)) /**< GPIO Port B Configuration Register High. */
#define GPIOB_IDR                 *((u32*)(GPIOB_Base_Address + 0x08)) /**< GPIO Port B Input Data Register. */
#define GPIOB_ODR                 *((u32*)(GPIOB_Base_Address + 0x0C)) /**< GPIO Port B Output Data Register. */
#define GPIOB_BSR                 *((u32*)(GPIOB_Base_Address + 0x10)) /**< GPIO Port B Bit Set Register. */
#define GPIOB_BRR                 *((u32*)(GPIOB_Base_Address + 0x14)) /**< GPIO Port B Bit Reset Register. */
#define GPIOB_LCK                 *((u32*)(GPIOB_Base_Address + 0x18)) /**< GPIO Port B Lock Register. */

/* REGISTERS ADDRESSES FOR Port C */
#define GPIOC_CRL                 *((u32*)(GPIOC_Base_Address + 0x00)) /**< GPIO Port C Configuration Register Low. */
#define GPIOC_CRH                 *((u32*)(GPIOC_Base_Address + 0x04)) /**< GPIO Port C Configuration Register High. */
#define GPIOC_IDR                 *((u32*)(GPIOC_Base_Address + 0x08)) /**< GPIO Port C Input Data Register. */
#define GPIOC_ODR                 *((u32*)(GPIOC_Base_Address + 0x0C)) /**< GPIO Port C Output Data Register. */
#define GPIOC_BSR                 *((u32*)(GPIOC_Base_Address + 0x10)) /**< GPIO Port C Bit Set Register. */
#define GPIOC_BRR                 *((u32*)(GPIOC_Base_Address + 0x14)) /**< GPIO Port C Bit Reset Register. */
#define GPIOC_LCK                 *((u32*)(GPIOC_Base_Address + 0x18)) /**< GPIO Port C Lock Register. */

#endif /* _GPIO_PRIVATE_H_ */
