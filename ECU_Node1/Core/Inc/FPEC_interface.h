/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :FPEC                        */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :October 15,2023             */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _FPEC_INTERFACE_H_
#define _FPEC_INTERFACE_H_

void FPEC_voidEraseAppArea(void);
	
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);

#endif
