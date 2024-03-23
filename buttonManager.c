/*
 * buttonManager.c
 *
 *  Created on: 29 nov. 2023
 *      Author: gabyd
 */

#include "buttonManager.h"

LED_state_t g_state = both_off_s;

motors_dir_t g_motor = forward_s;



void LED_R_on(void)
{
		GPIO_PortToggle(GPIOC, 1<<LED_R);

}

void LED_L_on(void)
{

		GPIO_PortToggle(GPIOC, 1<<LED_L);

}

void LED_on(void)
{
	GPIO_PortClear(GPIOC, 1 << LED_R);
	GPIO_PortClear(GPIOC, 1 << LED_L);

}

void LED_off(void)
{
	GPIO_PortSet(GPIOC, 1 << LED_R);
	GPIO_PortSet(GPIOC, 1 << LED_L);
}

void LED_Blink_on(void)
{

	if(TRUE == return_PIT0_status_flag() ){
		GPIO_PortToggle(GPIOC, 1<<LED_L);
		GPIO_PortToggle(GPIOC, 1<<LED_R);

		clear_pit0_status_flag();

	}


}

void LED_Left_Blink_on(void)
{

	if(TRUE == return_PIT0_status_flag() ){
		GPIO_PortToggle(GPIOC, 1<<LED_L);

		clear_pit0_status_flag();

	}


}


void LED_Right_Blink_on(void)
{

	if(TRUE == return_PIT0_status_flag() ){
		GPIO_PortToggle(GPIOC, 1<<LED_R);

		clear_pit0_status_flag();

	}


}

