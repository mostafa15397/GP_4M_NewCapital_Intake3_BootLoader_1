/*********************************************************/
/*Author    : Hagar tarek & Panssee mahmoud              */
/*SWC       : FPEC 				                         */
/*Layer     : MCAL                 					     */
/*Version   : 1.0                        				 */
/*Date      : October 10, 2023           				 */
/*Last Edit : N/A                        				 */
/*********************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ------------------------------------*/
/* USER CODE BEGIN PV */
u16 u16Data[100] = {0};
u32 u32Address = 0x08000000;
/* USER CODE END PV */


/**
  * @brief  Converts an ASCII character to its equivalent hexadecimal value.
  * @param  Copy_u8Asci: ASCII character to be converted.
  * @retval The equivalent hexadecimal value.
  */
u8 Parser_u8AsciToHex(u8 Copy_u8Asci)
{
    u8 Local_u8Result;
    /* Check if the received data is a number from 0 to 9 or a character from A to F */
    if ((Copy_u8Asci >= 48) && (Copy_u8Asci <= 57))
    {
        Local_u8Result = Copy_u8Asci - 48;
    }
    else
    {
        Local_u8Result = Copy_u8Asci - 55;
    }
    return Local_u8Result;
}

/**
  * @brief  Parses and writes data to the Flash memory based on the input buffer.
  * @param  Copy_u8BufData: Buffer containing the data to be parsed.
  * @return None
  */
void Pareser_voidParseData(u8 *Copy_u8BufData)
{
    u8 Local_u8DigitLow, Local_u8DigitHigh, Local_u8CC, Local_u8CounterData;
    u8 Local_u8DataDigit0, Local_u8DataDigit1, Local_u8DataDigit2, Local_u8DataDigit3;
    u8 Local_u8DataCounter = 0;

    /* Get Character Count */
    Local_u8DigitHigh = Parser_u8AsciToHex(Copy_u8BufData[1]);
    Local_u8DigitLow = Parser_u8AsciToHex(Copy_u8BufData[2]);
    Local_u8CC = (Local_u8DigitHigh << 4) | Local_u8DigitLow;

    /* Get Address */
    Local_u8DataDigit0 = Parser_u8AsciToHex(Copy_u8BufData[3]);
    Local_u8DataDigit1 = Parser_u8AsciToHex(Copy_u8BufData[4]);
    Local_u8DataDigit2 = Parser_u8AsciToHex(Copy_u8BufData[5]);
    Local_u8DataDigit3 = Parser_u8AsciToHex(Copy_u8BufData[6]);

    /* Clear Low Part of Address */
    u32Address = u32Address & 0xFFFF0000;
    u32Address = u32Address | (Local_u8DataDigit3) | (Local_u8DataDigit2 << 4) | (Local_u8DataDigit1 << 8) | (Local_u8DataDigit0 << 12);

    for (Local_u8CounterData = 0; Local_u8CounterData < Local_u8CC / 2; Local_u8CounterData++)
    {
        Local_u8DataDigit0 = Parser_u8AsciToHex(Copy_u8BufData[4 * Local_u8CounterData + 9]);
        Local_u8DataDigit1 = Parser_u8AsciToHex(Copy_u8BufData[4 * Local_u8CounterData + 10]);
        Local_u8DataDigit2 = Parser_u8AsciToHex(Copy_u8BufData[4 * Local_u8CounterData + 11]);
        Local_u8DataDigit3 = Parser_u8AsciToHex(Copy_u8BufData[4 * Local_u8CounterData + 12]);

        u16Data[Local_u8DataCounter] = (Local_u8DataDigit3 << 8) | (Local_u8DataDigit2 << 12) | (Local_u8DataDigit1) | (Local_u8DataDigit0 << 4);
        Local_u8DataCounter++;
    }

    FPEC_voidFlashWrite(u32Address, u16Data, Local_u8CC / 2);
}

/**
  * @brief  Parses and processes the upper address part of a record.
  * @param  Copy_u8BufferData: Buffer containing the upper address data.
  * @return None
  */
void Parser_voidParseUpperAddress(u8 *Copy_u8BufferData)
{
    // To be implemented based on requirements
}

/**
  * @brief  Parses and processes a record based on its type.
  * @param  Copy_u8BufferData: Buffer containing the record data.
  * @return None
  */
void Parser_voidParseRecord(u8 *Copy_u8BufferData)
{
    switch (Copy_u8BufferData[8])
    {
    case '0':
        Pareser_voidParseData(Copy_u8BufferData);
        break;
    case '4':
        Parser_voidParseUpperAddress(Copy_u8BufferData);
        break;
    }
}
