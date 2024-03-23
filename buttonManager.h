/*
 * buttonManager.h
 *
 *  Created on: 29 nov. 2023
 *      Author: gabyd
 */

#ifndef BUTTONMANAGER_H_
#define BUTTONMANAGER_H_

#include "gpio.h"
#include "pit.h"
#include "conversion.h"

typedef enum
{
	right_off_s,
	right_on_s,
	left_off_s,
	left_on_s,
	both_on_s,
	both_off_s
} LED_state_t;

typedef enum
{
	forward_s,
	backward_s
} motors_dir_t;

void leds_machine(void);

void motor_machine(void);

void LED_R_on(void);

void LED_L_on(void);

void LED_on(void);

void LED_Blink_on(void);

void LED_off(void);

void LED_Left_Blink_on(void);

void LED_Right_Blink_on(void);
#endif /* BUTTONMANAGER_H_ */
