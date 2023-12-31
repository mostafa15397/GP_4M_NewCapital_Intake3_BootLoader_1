/********************************************************/
/* Author    : Abanoub nader & Mostafa tawfik           */
/* SWC       : TIMER2             				        */
/* Layer     : MCAL                       				*/
/* Version   : 1.0                        				*/
/* Date      : October 16, 2023           				*/
/* Last Edit : N/A                        				*/
/********************************************************/

#ifndef _MTIMER2_PRIVATE_H_
#define _MTIMER2_PRIVATE_H_

/**
 * @struct MTIMER2_T
 * @brief TIMER2 Register Structure.
 */
typedef struct
{
    volatile u32 TIMER2_CR1;      /*!< Timer2 Control 1 register                  offset 0x00 */
    volatile u32 TIMER2_CR2;      /*!< Timer2 Control 2 register                  offset 0x04 */
    volatile u32 TIMER2_SMCR;     /*!< Timer2 slave mode control register         offset 0x08 */
    volatile u32 TIMER2_DIER;     /*!< Timer2 DMA interrupt enable register       offset 0x0C */
    volatile u32 TIMER2_SR;       /*!< Timer2 status register                     offset 0x10 */
    volatile u32 TIMER2_EGR;      /*!< Timer2 event generation register           offset 0x14 */
    volatile u32 TIMER2_CCMR1;    /*!< Timer2 capture/compare 1 register          offset 0x18 */
    volatile u32 TIMER2_CCMR2;    /*!< Timer2 capture/compare 2 register          offset 0x1C */
    volatile u32 TIMER2_CCER;     /*!< Timer2 capture/compare enable register     offset 0x20 */
    volatile u32 TIMER2_CNT;      /*!< Timer2 counter register                    offset 0x24 */
    volatile u32 TIMER2_PSC;      /*!< Timer2 prescaler register                  offset 0x28 */
    volatile u32 TIMER2_ARR;      /*!< Timer2 auto reload register                offset 0x2C */
    volatile u32 RESERVE1;        /*!< Reserve                                     offset 0x30 */
    volatile u32 TIMER2_CCR1;     /*!< Timer2 capture/compare 1 register          offset 0x34 */
    volatile u32 TIMER2_CCR2;     /*!< Timer2 capture/compare 2 register          offset 0x38 */
    volatile u32 TIMER2_CCR3;     /*!< Timer2 capture/compare 3 register          offset 0x3C */
    volatile u32 TIMER2_CCR4;     /*!< Timer2 capture/compare 4 register          offset 0x40 */
    volatile u32 RESERVE2;        /*!< Reserve                                     offset 0x44 */
    volatile u32 TIMER2_DCR;      /*!< Timer2 DMA control register                 offset 0x48 */
    volatile u32 TIMER2_DMAR;     /*!< Timer2 DMA address for full transfer register  offset 0x4C */

} MTIMER2_T;

/** @brief TIMER2 Base Address */
#define MTIMER2_BASE_ADDRESS (0x40000000)
/** @brief TIMER2 Register Definition */
#define TIMER2 ((volatile MTIMER2_T *)MTIMER2_BASE_ADDRESS)

/** @brief Definitions for TIMER2_CR1 register */
#define CR1_CEN 0
#define CR1_UDIS 1
#define CR1_ARPE 7

/** @brief Definitions for TIMER2_EGR register */
#define EGR_UG 0

/** @brief Definitions for TIMER2_CCMR1 register */
#define CCMR1_OC2M 12
#define CCMR1_OC2PE 11

/** @brief Definitions for TIMER2_CCER register */
#define CCER_CC2E 4

/** @brief Definitions for Masking TIMER2_PWM_MODE_MUSK register */
#define MTIMER2_PWM_MODE_MUSK 0xFFFF87FF

#endif /* _MTIMER2_PRIVATE_H_ */

/**
 * @} // end of TIMER2_PRIVATE group
 */
