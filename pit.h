/*
 * pit.h
 *
 *  Created on: 22 sep. 2023
 *      Author: gabyd
 */

#ifndef PIT_H_
#define PIT_H_

#include "fsl_pit.h"
#include "gpio.h"

#define PIT_BASEADDR PIT
#define PIT_CHANNEL  kPIT_Chnl_0
#define PIT_CHANNEL_1  kPIT_Chnl_1
#define PIT_IRQ_ID   PIT0_IRQn

#define PIT1_CHANNEL  kPIT_Chnl_1
#define PIT1_IRQ_ID   PIT1_IRQn

#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define PIT_CLOCK_GATING  0x800000
#define PIT_MDIS_ENABLE   0x2


/*! This enumerated constant are used to select the PIT to be used*/
typedef enum
		{
			PIT_0,
			PIT_1,
			PIT_2,
			PIT_3
		} PIT_timer_t;


void init_PIT0();
void init_PIT1();

void PIT_callback_init(PIT_timer_t pit, void(*handler)(void));

bool_t return_PIT0_status_flag(void);

void clear_pit0_status_flag(void);

bool_t return_PIT1_status_flag(void);

void clear_pit1_status_flag(void);

#endif /* PIT_H_ */
