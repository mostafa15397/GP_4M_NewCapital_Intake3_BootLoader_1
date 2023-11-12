/*********************************************************/
/* Author    : Amir khalifa & Mostafa tawfik             */
/* SWC       : IR Sensor              					 */
/* Layer     : HCAL                     				 */
/* Version   : 1.0                      				 */
/* Date      : October 17, 2023          				 */
/* Last Edit : N/A                      				 */
/*********************************************************/

#ifndef _IR_SENSOR_INTERFACE_H_
#define _IR_SENSOR_INTERFACE_H_

/**
 * @brief Initializes the IR Sensor GPIO pins.
 * @note This function configures the GPIO pins connected to the IR sensor as floating inputs.
 */
void IR_SENSOR_voidInti(void);

/**
 * @brief Reads the right IR sensor.
 * @note This function reads the digital value of the right IR sensor pin.
 * @return u8: Digital value (0 or 1) indicating the IR sensor reading.
 */
u8 IR_SENSOR_u8GetRightReading(void);

/**
 * @brief Reads the left IR sensor.
 * @note This function reads the digital value of the left IR sensor pin.
 * @return u8: Digital value (0 or 1) indicating the IR sensor reading.
 */
u8 IR_SENSOR_u8GetLeftReading(void);

#endif /* _IR_SENSOR_INTERFACE_H_ */

/** @} */
