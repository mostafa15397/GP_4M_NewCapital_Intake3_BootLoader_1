/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_INTERFACE.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"
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

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
 * @brief Configures the EXTI line for a specific pin.
 * @param LOC_u8EXTI_Line: EXTI line number (0 to 15).
 * @param LOC_u8PortMap: Port source mapping for EXTI (0 to 0xF).
 * @note This function configures the EXTI line for a specific pin based on the EXTI line number and port mapping.
 * @return None
 */
void AFIO_ViodSetEXTIConfiguration(u8 LOC_u8EXTI_Line, u8 LOC_u8PortMap) {

    u8 LOC_u8RegIndex = 0;

    if (LOC_u8EXTI_Line <= 3) {
        LOC_u8RegIndex = 0;
    } else if (LOC_u8EXTI_Line <= 7) {
        LOC_u8RegIndex = 1;
        LOC_u8EXTI_Line -= 4;
    } else if (LOC_u8EXTI_Line <= 11) {
        LOC_u8RegIndex = 2;
        LOC_u8EXTI_Line -= 8;
    } else if (LOC_u8EXTI_Line <= 15) {
        LOC_u8RegIndex = 3;
        LOC_u8EXTI_Line -= 12;
    }

    AFIO->EXTICRx[LOC_u8RegIndex] &= ~((0b1111) << (LOC_u8EXTI_Line * 4));  // Read-Modify-Write
    AFIO->EXTICRx[LOC_u8RegIndex] |= (LOC_u8PortMap) << (LOC_u8EXTI_Line * 4);
}

/**
 * @brief Configures the remapping of Timer2.
 * @param Local_u8Timer2Map: Timer2 remapping option.
 *        - TIMER2_NOREMAPPED: No remapping.
 *        - TIMER2_PARTIALREMAPPED_1: Partial remapping option 1.
 *        - TIMER2_PARTIALREMAPPED_2: Partial remapping option 2.
 *        - TIMER2_FULLYREMAPPED: Fully remapped.
 * @note This function configures the remapping of Timer2 based on the selected option.
 * @return None
 */
void AFIO_viodSetTimer2Configuration(u8 Local_u8Timer2Map) {
    switch (Local_u8Timer2Map) {
        case TIMER2_NOREMAPPED:
            CLR_BIT(AFIO->MAPR, 8);
            CLR_BIT(AFIO->MAPR, 9);
            break;
        case TIMER2_PARTIALREMAPPED_1:
            SET_BIT(AFIO->MAPR, 8);
            CLR_BIT(AFIO->MAPR, 9);
            break;
        case TIMER2_PARTIALREMAPPED_2:
            CLR_BIT(AFIO->MAPR, 8);
            SET_BIT(AFIO->MAPR, 9);
            break;
        case TIMER2_FULLYREMAPPED:
            SET_BIT(AFIO->MAPR, 8);
            SET_BIT(AFIO->MAPR, 9);
            break;
        default:
            break;
    }
}
