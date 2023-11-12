/*******************************************************/
/* Author    : Amir khalifa & Mohamed mahmoud          */
/* SWC       : RCC                        			   */
/* Layer     : MCAL                         		   */
/* Version   : 1.0                        			   */
/* Date      : October 16, 2023            			   */
/* Last Edit : N/A                        			   */
/*******************************************************/

#ifndef _RCC_PRIVATE_H_
#define _RCC_PRIVATE_H_

/* Register Definitions */
#define RCC_CR         *((u32*)0x40021000) /**< Clock Control Register */
#define RCC_CFGR       *((u32*)0x40021004) /**< Clock Configuration Register */
#define RCC_CIR        *((u32*)0x40021008) /**< Clock Interrupt Register */
#define RCC_APB2RSTR   *((u32*)0x4002100C) /**< APB2 Peripheral Reset Register */
#define RCC_APB1RSTR   *((u32*)0x40021010) /**< APB1 Peripheral Reset Register */
#define RCC_AHBENR     *((u32*)0x40021014) /**< AHB Bus Clock Enable Register */
#define RCC_APB2ENR    *((u32*)0x40021018) /**< APB2 Peripheral Clock Enable Register */
#define RCC_APB1ENR    *((u32*)0x4002101C) /**< APB1 Peripheral Clock Enable Register */
#define RCC_BDCR       *((u32*)0x40021020) /**< Backup Domain Control Register */
#define RCC_CSR        *((u32*)0x40021024) /**< Clock Control & Status Register */

/* Clock Types */
#define RCC_HSE_CRYSTAL      0 /**< External High-Speed Clock using Crystal Oscillator */
#define RCC_HSE_RC           1 /**< External High-Speed Clock using RC Oscillator */
#define RCC_HSI              2 /**< Internal High-Speed Clock */
#define RCC_PLL              3 /**< Phase-Locked Loop Clock */

/* PLL Options */
#define RCC_PLL_IN_HSI_DIV_2  0 /**< PLL input source: HSI divided by 2 */
#define RCC_PLL_IN_HSE_DIV_2  1 /**< PLL input source: HSE divided by 2 */
#define RCC_PLL_IN_HSE        2 /**< PLL input source: HSE */

#endif

/** @} */
