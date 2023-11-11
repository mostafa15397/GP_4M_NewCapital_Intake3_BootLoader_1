/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :SYSTICK                     */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 3,2023            */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _SYSTICK_PRIVATE_H_
#define _SYSTICK_PRIVATE_H_

typedef struct
{
	volatile u32 CTRL  ;
	volatile u32 LOAD  ;
	volatile u32 VAL   ;
}STK_t;

#define     SYSTICK    ((STK_t*)0xE000E010)

#define     SYSTICK_SRC_AHB           0
#define     SYSTICK_SRC_AHB_8         1

#define     SYSTICK_SINGLE_INTERVAL    0
#define     SYSTICK_PERIOD_INTERVAL    1

#endif
