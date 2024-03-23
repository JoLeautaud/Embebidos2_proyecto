/*
 * states_machine.h
 *
 *  Created on: 30 nov. 2023
 *      Author: gabyd
 */

#ifndef STATES_MACHINE_H_
#define STATES_MACHINE_H_

typedef enum
{
	ADELANTE,
	ATRAS
}States_t;

typedef enum
{
	OFF,
	BLINKER,
	LEFT_LED,
	RIGHT_LED
}StatesLEDs_t;

void initial_machine(void);
void machine_blink(void);

#endif /* STATES_MACHINE_H_ */
