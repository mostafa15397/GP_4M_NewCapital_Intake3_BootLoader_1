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

u16 u16Data[100] = {0};
u32 u32Address= 0x08000000;

u8 Parser_u8AsciToHex(u8 Copy_u8Asci)
{
	u8 Local_u8Result;
	/* check received data */
	/* if it is number from 0 to 9 */
	/* or it is character from A TO F */
	/* to change it from ASCI to Decimal */
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Local_u8Result = Copy_u8Asci - 48;
	}
	else
	{
		Local_u8Result = Copy_u8Asci - 55;
	}
	return Local_u8Result ;
}

void Pareser_voidParseData(u8* Copy_u8BufData)
{
	u8 Local_u8DigitLow,Local_u8DigitHigh,Local_u8CC,Local_u8CounterData;
	u8 Local_u8DataDigit0,Local_u8DataDigit1,Local_u8DataDigit2,Local_u8DataDigit3;
	u8 Local_u8DataCounter = 0;

	/* Get Character Count */
	Local_u8DigitHigh = Parser_u8AsciToHex (Copy_u8BufData[1]);
	Local_u8DigitLow  = Parser_u8AsciToHex (Copy_u8BufData[2]);
	Local_u8CC        = (Local_u8DigitHigh<<4) | Local_u8DigitLow ;

	/* Get Address */
	Local_u8DataDigit0 = Parser_u8AsciToHex (Copy_u8BufData[3]);
	Local_u8DataDigit1 = Parser_u8AsciToHex (Copy_u8BufData[4]);
	Local_u8DataDigit2 = Parser_u8AsciToHex (Copy_u8BufData[5]);
	Local_u8DataDigit3 = Parser_u8AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	u32Address = u32Address & 0xFFFF0000;
	u32Address = u32Address | (Local_u8DataDigit3) | (Local_u8DataDigit2 << 4) | (Local_u8DataDigit1 << 8) | (Local_u8DataDigit0<<12);

	for (Local_u8CounterData = 0 ; Local_u8CounterData < Local_u8CC/2; Local_u8CounterData++)
	{
		Local_u8DataDigit0 = Parser_u8AsciToHex (Copy_u8BufData[4*Local_u8CounterData+9 ]);
		Local_u8DataDigit1 = Parser_u8AsciToHex (Copy_u8BufData[4*Local_u8CounterData+10]);
		Local_u8DataDigit2 = Parser_u8AsciToHex (Copy_u8BufData[4*Local_u8CounterData+11]);
		Local_u8DataDigit3 = Parser_u8AsciToHex (Copy_u8BufData[4*Local_u8CounterData+12]);

		u16Data[Local_u8DataCounter] = (Local_u8DataDigit3 << 8) | (Local_u8DataDigit2 << 12) | (Local_u8DataDigit1) | (Local_u8DataDigit0<<4);
		Local_u8DataCounter++;
	}

	FPEC_voidFlashWrite(u32Address , u16Data , Local_u8CC/2 );
}

void Parser_voidParseUpperAddress(u8* Copy_u8BufferData)
{
//	u8 Local_u8DataDigit0,Local_u8DataDigit1,Local_u8DataDigit2,Local_u8DataDigit3;
//	/* Get  high part of Address */
//	Local_u8DataDigit0 = Parser_u8AsciToHex (Copy_u8BufferData[3]);
//	Local_u8DataDigit1 = Parser_u8AsciToHex (Copy_u8BufferData[4]);
//	Local_u8DataDigit2 = Parser_u8AsciToHex (Copy_u8BufferData[5]);
//	Local_u8DataDigit3 = Parser_u8AsciToHex (Copy_u8BufferData[6]);
//	/* Clear Low Part of Address */
//	u32Address = u32Address & (u32)0x0000FFFF;
//	u32Address = u32Address | (u32)((u32)(Local_u8DataDigit3 << 28) | (u32)(Local_u8DataDigit2 << 24) | (u32)(Local_u8DataDigit1 << 20) | (u32)(Local_u8DataDigit0 << 16));
}

void Parser_voidParseRecord(u8* Copy_u8BufferData)
{
	switch (Copy_u8BufferData[8])
	{
	case '0': Pareser_voidParseData(Copy_u8BufferData); break;
	case '4': Parser_voidParseUpperAddress(Copy_u8BufferData); break;
	}
}
