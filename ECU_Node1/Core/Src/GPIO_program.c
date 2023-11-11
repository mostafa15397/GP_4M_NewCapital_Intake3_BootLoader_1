/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :GPIO                        */
/*Layer     :MCAL                        */
/*Version   :1.0                         */
/*Date      :September 1,2023            */
/*Last Edit :N/A                         */
/*****************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"


/**
 * @brief GPIO Set pin direction Function
 * @param The first parameter is the Port
 * @param The second parameter is Pin
 * @param The Third parameter is the Mode of Input pin or output pin
 * @retval None
 */

void GPIO_VidSetPinDirection( u8 Copy_u8Port , u8 Copy_u8Pin , u8 u8Copy_u8Mode )
{
	switch(Copy_u8Port)
	{
		case DIOA:
			if(Copy_u8Pin <= 7 )
			{//low
				GPIOA_CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ));// R M W
				GPIOA_CRL |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 );
			}
			else if(Copy_u8Pin <=15 )
			{//high
				Copy_u8Pin = Copy_u8Pin - 8;
				GPIOA_CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
				GPIOA_CRH |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 );
			}
			break;
		case DIOB:
			if(Copy_u8Pin <= 7 )
			{//low
				GPIOB_CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );// R M W
				GPIOB_CRL |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
			}
			else if(Copy_u8Pin <=15 )
			{//high
				Copy_u8Pin = Copy_u8Pin - 8;
				GPIOB_CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
				GPIOB_CRH |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
			}
			break;
		case DIOC:
			if(Copy_u8Pin <= 7 )
			{//low
				GPIOC_CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );// R M W
				GPIOC_CRL |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
			}
			else if(Copy_u8Pin <=15 )
			{//high
				Copy_u8Pin = Copy_u8Pin - 8;
				GPIOC_CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
				GPIOC_CRH |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
			}
			break;
		default :break;
	}
}

/**
 * @brief GPIO Set pin Value Function
 * @param The first parameter is the Port
 * @param The second parameter is Pin
 * @param The Third parameter is the Value of the pin low/high
 * @retval None
 */

void GPIO_VidSetPinValue( u8 Copy_u8Port , u8 Copy_u8Pin , u8 u8Copy_u8Value )
{
	switch(Copy_u8Port)
	{
		case DIOA:
			if( u8Copy_u8Value == HIGH )
			{
				SETBIT( GPIOA_ODR , Copy_u8Pin );
			}
			else if( u8Copy_u8Value == LOW )
			{
				CLR_BIT(  GPIOA_ODR , Copy_u8Pin );
			}
			break;
		case DIOB:
			if( u8Copy_u8Value == HIGH )
			{
				SETBIT( GPIOB_ODR  , Copy_u8Pin );
			}
			else if( u8Copy_u8Value == LOW )
			{
				CLR_BIT( GPIOB_ODR  , Copy_u8Pin );
			}
			break;
		case DIOC:
			if( u8Copy_u8Value == HIGH )
			{
				SETBIT( GPIOC_ODR , Copy_u8Pin );
			}
			else if( u8Copy_u8Value == LOW )
			{
				CLR_BIT( GPIOC_ODR , Copy_u8Pin );
			}
			break;
	}
}

u8   GPIO_u8GetPinValue( u8 Copy_u8Port , u8 Copy_u8Pin )
{
	u8 Local_u8Result = 0 ;
	switch(Copy_u8Port)
	{
		case DIOA: Local_u8Result = GET_BIT( GPIOA_IDR , Copy_u8Pin ); break;
		case DIOB: Local_u8Result = GET_BIT( GPIOB_IDR , Copy_u8Pin ); break;
		case DIOC: Local_u8Result = GET_BIT( GPIOC_IDR , Copy_u8Pin ); break;
	}
	return Local_u8Result;
}
