/************************************************************/
/* Author    : Mostafa tawfik & Panssee mahmoud             */
/* SWC       : UART1                      					*/
/* Layer     : MCAL                       					*/
/* Version   : 1.0                        					*/
/* Date      : October 14, 2023         					*/
/* Last Edit : N/A                        					*/
/************************************************************/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"
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
  * @brief  Initialize UART1 with a baud rate of 9600, enabling transmitter and receiver.
  * @param  None
  * @note   This function configures UART1 with a specific baud rate, enables the transmitter
  *         and receiver, and enables the USART.
  * @return None
  */
void UART1_voidInit(void)
{
    /* Set the baud rate to 9600 */
    UART1->BRR = 0x341;
    /* Enable Transmitter */
    SETBIT((UART1->CR[0]), 3);
    /* Enable Receiver */
    SETBIT((UART1->CR[0]), 2);
    /* Enable USART */
    SETBIT((UART1->CR[0]), 13);
    /* Clear the status register */
    UART1->SR = 0;
}

/**
  * @brief  Transmit a string of data using UART1.
  * @param  copy_u8Data: The string to be transmitted.
  * @note   This function transmits a string of data using UART1. It waits for each character
  *         to be sent and then proceeds to the next one.
  * @return None
  */
void UART1_voidTransmit(u8 copy_u8Data[])
{
    u8 Local_u8DataCounter = 0;
    while (copy_u8Data[Local_u8DataCounter] != '\0')
    {
        /* Put data in the sender buffer */
        UART1->DR = copy_u8Data[Local_u8DataCounter];
        /* Wait till the transmission is complete */
        while ((GET_BIT((UART1->SR), 6)) == 0);
        /* Move to the next element of data */
        Local_u8DataCounter++;
    }
}

/**
  * @brief  Transmit a single ASCII character using UART1.
  * @param  value: The ASCII character to be transmitted.
  * @note   This function transmits a single ASCII character using UART1.
  *         It waits for the transmission to complete before returning.
  * @return None
  */
void UART1_voidTransmitASCI(u8 value)
{
    /* Put data in the sender buffer */
    UART1->DR = value;
    /* Wait till the transmission is complete */
    while ((GET_BIT((UART1->SR), 6)) == 0);
}

/**
  * @brief  Receive a character using UART1.
  * @param  Copy_u8Data: Pointer to the variable where the received data will be stored.
  * @return 1 if data is received, 0 if no data is received.
  */
u8 UART1_u8Receive(u8* Copy_u8Data)
{
    u8 Local_u8Result = 1;
    /* Check if there is received data */
    if ((GET_BIT((UART1->SR), 5)) == 1)
    {
        *Copy_u8Data = UART1->DR;
    }
    else
    {
        Local_u8Result = 0;
    }
    return Local_u8Result;
}
