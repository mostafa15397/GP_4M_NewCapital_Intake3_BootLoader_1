#ifndef _AFIO_PRIVATE_H_
#define _AFIO_PRIVATE_H_

/** AFIO Register Structure */
typedef struct
{
    volatile u32 EVCR;          /**< Event Control Register */
    volatile u32 MAPR;          /**< AF remap and debug I/O configuration register */
    volatile u32 EXTICRx[4];    /**< External interrupt configuration registers (0 to 3) */
    volatile u32 MAPR2;         /**< AF remap and debug I/O configuration register 2 */
} AFIO_Type;

/** AFIO Base Address */
#define AFIO ((volatile AFIO_Type *) 0x40010000)

#endif /* _AFIO_PRIVATE_H_ */

/** @} */
