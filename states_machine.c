/*
 * states_machine.c
 *
 *  Created on: 30 nov. 2023
 *      Author: gabyd
 */

#include "states_machine.h"
#include "gpio.h"
#include "conversion.h"
#include "adc.h"
#include "pit.h"
#include "buttonManager.h"

States_t g_states = ADELANTE;
StatesLEDs_t g_states_leds = OFF;

void initial_machine(void)
{
	uint32_t adcValueMotor = ADC_Read_Motor();

	switch(g_states)
	{
	case(ADELANTE):

		AdcToPwmMotor(adcValueMotor);

		if(get_reverse_pressed_flag())
		{
			g_states = ATRAS;

			set_reverse_pressed_flag(FALSE);
		}

	break;
	case(ATRAS):


		AdcToPwmMotorBwd(adcValueMotor);

		if(get_reverse_pressed_flag())
		{
			g_states = ADELANTE;
			set_reverse_pressed_flag(FALSE);
		}


	break;

	}
}

void machine_blink(void)
{

	switch(g_states_leds)
	{
	case(OFF):

		LED_off();

			if(get_blink_pressed_flag()){

				g_states_leds = BLINKER;
				set_blink_pressed_flag(FALSE);

			}


			if(get_right_pressed_flag()){

				g_states_leds = RIGHT_LED;
				set_right_pressed_flag(FALSE);
			}

			if(get_left_pressed_flag()){
				g_states_leds = LEFT_LED;
				set_left_pressed_flag(FALSE);
			}

	break;
	case(BLINKER):


		PIT_StartTimer(PIT, PIT_0);
		LED_Blink_on();

		if(get_blink_pressed_flag()){

			g_states_leds = OFF;
			set_blink_pressed_flag(FALSE);

		}
	break;

	case(LEFT_LED):
		PIT_StartTimer(PIT, PIT_0);
		LED_Left_Blink_on();

		if(get_left_pressed_flag()){

			g_states_leds = OFF;
			set_left_pressed_flag(FALSE);

			}

	break;

	case(RIGHT_LED):

		PIT_StartTimer(PIT, PIT_0);
		LED_Right_Blink_on();

		if(get_right_pressed_flag()){

			g_states_leds = OFF;
			set_right_pressed_flag(FALSE);

			}
	break;

	}





}
