/*********************************************************/
/* Author    : Hagar tarek & Panssee mahmoud             */
/* SWC       : FPEC                       			     */
/* Layer     : MCAL                       				 */
/* Version   : 1.0                        				 */
/* Date      : October  8, 2023           				 */
/* Last Edit : N/A                        				 */
/*********************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Erases the application area of the Flash memory.
  * @param  None
  * @note   This function erases all pages from page 4 to page 63.
  * @return None
  */
void FPEC_voidEraseAppArea(void)
{
    u8 Local_u8PageNumber;
    for (Local_u8PageNumber = 4; Local_u8PageNumber < 64; Local_u8PageNumber++)
    {
        /* Send the page number to erase it */
        FPEC_voidFlashPageErase(Local_u8PageNumber);
    }
}

/**
  * @brief  Erases a specified page in the Flash memory.
  * @param  Copy_u8PageNumber: The page number to be erased.
  *         This should be in the range of 4 to 63 for the application area.
  * @return None
  */
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
    /* Wait for the Busy Flag */
    while (GET_BIT(FPEC->SR, 0) == 1);
    
    /* Check if FPEC is locked or not */
    if (GET_BIT(FPEC->CR, 7) == 1)
    {
        FPEC->KEYR = 0x45670123;
        FPEC->KEYR = 0xCDEF89AB;
    }
    
    /* Page Erase Operation */
    SETBIT(FPEC->CR, 1);
    
    /* Write Page address */
    FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000;

    /* Start operation */
    SETBIT(FPEC->CR, 6);

    /* Wait for the Busy Flag */
    while (GET_BIT(FPEC->SR, 0) == 1);
    
    /* End of operation (EOP) */
    SETBIT(FPEC->SR, 5);
    CLR_BIT(FPEC->CR, 1);
}
 /**
 * @brief  Writes data to the Flash memory starting from a specified address.
 * @param  Copy_u32Address: Pointer to the starting address to write data to.
 * @param  Copy_u16Data: Pointer to an array of 16-bit data to be written.
 * @param  Copy_u8Length: The length of the data array.
 * @note   This function writes half-word data to consecutive addresses in the Flash memory.
 * @return None
 */
void FPEC_voidFlashWrite(u32 *Copy_u32Address, u16 *Copy_u16Data, u8 Copy_u8Length)
{
    u8 Local_DataCounter;

    /* Wait for the Busy Flag */
    while (GET_BIT(FPEC->SR, 0) == 1);

    /* Check if FPEC is locked or not */
    if (GET_BIT(FPEC->CR, 7) == 1)
    {
        FPEC->KEYR = 0x45670123;
        FPEC->KEYR = 0xCDEF89AB;
    }

    for (Local_DataCounter = 0; Local_DataCounter < Copy_u8Length; Local_DataCounter++)
    {
        /* Write Flash Programming */
        SET_BIT(FPEC->CR, 0);

        /* Half-word operation */
        *((volatile u16 *)(*Copy_u32Address)) = Copy_u16Data[Local_DataCounter];
        (*Copy_u32Address) += 2;

        /* Wait for the Busy Flag */
        while (GET_BIT(FPEC->SR, 0) == 1);

        /* End of operation (EOP) */
        SET_BIT(FPEC->SR, 5);
        CLR_BIT(FPEC->CR, 0);
    }
}

