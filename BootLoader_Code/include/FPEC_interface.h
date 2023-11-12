/*********************************************************/
/* Author    : Hagar tarek & Panssee mahmoud             */
/* SWC       : FPEC                       			     */
/* Layer     : MCAL                       				 */
/* Version   : 1.0                        				 */
/* Date      : October  8, 2023           				 */
/* Last Edit : N/A                        				 */
/*********************************************************/

#ifndef _FPEC_INTERFACE_H_
#define _FPEC_INTERFACE_H_

/**
 * @brief Erases the application area of the Flash memory.
 * @details This function erases all pages from page 4 to page 63.
 * @return None
 */
void FPEC_voidEraseAppArea(void);

/**
 * @brief Erases a specified page in the Flash memory.
 * @details This function erases a specified page in the Flash memory.
 * @param Copy_u8PageNumber: The page number to be erased. Should be in the range of 4 to 63 for the application area.
 * @return None
 */
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

/**
 * @brief Writes data to the Flash memory starting from a specified address.
 * @details This function writes half-word data to consecutive addresses in the Flash memory.
 * @param Copy_u32Address: Pointer to the starting address to write data to.
 * @param Copy_u16Data: Pointer to an array of 16-bit data to be written.
 * @param Copy_u8Length: The length of the data array.
 * @note This function writes half-word data to consecutive addresses in the Flash memory.
 * @return None
 */
void FPEC_voidFlashWrite(u32 *Copy_u32Address, u16 *Copy_u16Data, u8 Copy_u8Length);

#endif /* _FPEC_INTERFACE_H_ */
