/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :FPEC                        */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :October 15,2023             */
/*Last Edit :N/A                         */
/*****************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


/**
 * @brief Flash Erase Function to Erase  all Flash memory
 * @param  None
 * @retval None
 */
void FPEC_voidEraseAppArea(void)
{
	u8 Local_u8PageNumber;
	for (Local_u8PageNumber = 4 ; Local_u8PageNumber < 64 ; Local_u8PageNumber++)
	{
		/* send the page number to erase it */
		FPEC_voidFlashPageErase(Local_u8PageNumber);
	}
}

/**
 * @brief Flash Erase Function to Erase  specific page in  Flash memory
 * @param  Page number which want to Erass
 * @retval None
 */
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while(GET_BIT(FPEC->SR,0) == 1);
	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,7) == 1)
	{
		FPEC->KEYR = 0x45670123;
		FPEC->KEYR = 0xCDEF89AB;
	}
	/* Page Erase Operation */
	SETBIT(FPEC->CR,1);
	/* Write Page address */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;
	/* Start operation */
	SETBIT(FPEC->CR,6);
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);
	/* EOP */
	SETBIT(FPEC->SR,5);
	CLR_BIT(FPEC->CR,1);
}
/**
 * @brief Flash Write Function to write data on address on flash memory
 * @param  the first is address of location which want to write on it
 * @param  the second is the  buffur of data which want to burn it
 * @param  the third is the length of buffr of data
 * @retval None
 */
void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 Local_DataCounter;
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);
	/* Check if FPEC is locked or not */
	if ( /* FPEC_CR->BitAccess.LOCK == 1 */ GET_BIT(FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	for (Local_DataCounter = 0; Local_DataCounter< Copy_u8Length; Local_DataCounter++)
	{
		/* Write Flash Programming */
		SETBIT(FPEC->CR,0);
		/* Half word operation */
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[Local_DataCounter];
		Copy_u32Address += 2 ;
		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,0) == 1);
		/* EOP */
		SETBIT(FPEC->SR,5);
		CLR_BIT(FPEC->CR,0);
	}
}
