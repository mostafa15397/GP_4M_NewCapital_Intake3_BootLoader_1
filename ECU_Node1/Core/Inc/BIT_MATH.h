/*****************************************/
/*Author    :Abanoub Nader               */
/*SWC       :BIT MATH                    */
/*Layer     :LIB                         */
/*Version   :1.0                         */
/*Date      :August 25,2023              */
/*Last Edit :N/A                         */
/*****************************************/

#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

#define SET_BIT(VAR,BIT)          VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)          VAR &= ~(1 << (BIT)) 
#define GET_BIT(VAR,BIT)          ((VAR >> BIT) & 1  )
#define TOG_BIT(VAR,BIT)          VAR ^=  (1 << (BIT))

#endif 
