/*
 * Direction.c
 *
 *  Created on: 22 nov. 2023
 *      Author: gabyd
 */
#include "conversion.h"


void AdcToPwmServo(uint32_t value)
{
	if (value > ADC_MAX_VALUE)
	{
	    value = ADC_MAX_VALUE;
	}
    // Realizar la conversión
    uint32_t calcValue= ((value * 255) / ADC_MAX_VALUE);
    FlexTimer_updateCH1Value(calcValue);
}


void AdcToPwmMotor(uint32_t value)
{
	bool_t bandera_reverse = FALSE;
    // Ajustar el valor si está fuera del rango
    if (value < ADC_MIN_VALUE)
    {
        value = ADC_MIN_VALUE;
    }
    else if (value > ADC_MAX_VALUE)
    {
        value = ADC_MAX_VALUE;
    }

    // Calcular el valor del PWM dentro del nuevo rango
    uint32_t calcValue = ((value - ADC_MIN_VALUE) * 255) / (ADC_MAX_VALUE - ADC_MIN_VALUE);


    moveForward(calcValue);
}

void AdcToPwmMotorBwd(uint32_t value)
{
    // Ajustar el valor si está fuera del rango
    if (value < ADC_MIN_VALUE)
    {
        value = ADC_MIN_VALUE;
    }
    else if (value > ADC_MAX_VALUE)
    {
        value = ADC_MAX_VALUE;
    }

    // Calcular el valor del PWM dentro del nuevo rango
    uint32_t calcValue = ((value - ADC_MIN_VALUE) * 255) / (ADC_MAX_VALUE - ADC_MIN_VALUE);


    moveBackward(calcValue);
}


