/*
 * adc.h
 *
 *  Created on: 20 nov. 2023
 *      Author: gabyd
 */

#ifndef ADC_H_
#define ADC_H_

#include "clock_config.h"
#include "board.h"
#include "fsl_adc16.h"
#include "gpio.h"


void ADC_Init(void);
uint16_t ADC_Read_Servo(void);
uint16_t ADC_Read_Motor(void);
bool_t return_ADC_status_flag(void);
void clear_ADC_status_flag(void);

#endif /* ADC_H_ */
