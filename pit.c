/*
 * pit.c
 *
 *  Created on: 22 sep. 2023
 *      Author: gabyd
 */
#include "pit.h"

/*Callbacks for each channel*/
static void (*PIT_CH0_callback)(void) = 0;
static void (*PIT_CH1_callback)(void) = 0;
static void (*PIT_CH2_callback)(void) = 0;
static void (*PIT_CH3_callback)(void) = 0;

bool_t pit_status_flag = FALSE;
bool_t pit1_status_flag = FALSE;
bool_t pit0_status_flag = FALSE;



void init_PIT0()
{
	 /* Structure of initialize PIT */
	pit_config_t pitConfig;
    /*
     * pitConfig.enableRunInDebug = false;
     */
    PIT_GetDefaultConfig(&pitConfig);

    /* Init pit module */
    PIT_Init(PIT_BASEADDR, &pitConfig);

    /* Set timer period for channel 0 */
    PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(500000u,PIT_SOURCE_CLOCK));

    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(PIT_IRQ_ID);
}



void init_PIT1()
{
	 /* Structure of initialize PIT */
	pit_config_t pitConfig;
    /*
     * pitConfig.enableRunInDebug = false;
     */
    PIT_GetDefaultConfig(&pitConfig);

    /* Init pit module */
    PIT_Init(PIT_BASEADDR, &pitConfig);

    /* Set timer period for channel 0 */
    PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL_1, USEC_TO_COUNT(100000u,PIT_SOURCE_CLOCK));

    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL_1, kPIT_TimerInterruptEnable);

    PIT_StartTimer(PIT_BASEADDR, PIT1_CHANNEL);

    /* Enable at the NVIC */
    EnableIRQ(PIT1_IRQ_ID);


}



void PIT0_IRQHandler(void)
{
	pit_status_flag = TRUE;
	if(PIT_CH0_callback)
	{
		PIT_CH0_callback();
	}
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}

void PIT1_IRQHandler(void)
{
	pit1_status_flag = TRUE;
	if(PIT_CH1_callback)
	{
		PIT_CH1_callback();
	}
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
}

void PIT2_IRQHandler(void)
{
	if(PIT_CH2_callback)
	{
		PIT_CH2_callback();
	}
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
}

void PIT3_IRQHandler(void)
{
	if(PIT_CH3_callback)
	{
		PIT_CH3_callback();
	}
	PIT->CHANNEL[3].TFLG |= PIT_TFLG_TIF_MASK;
}

void PIT_callback_init(PIT_timer_t pit, void(*handler)(void))
{
	switch (pit)
		{
		case PIT_0:
			PIT_CH0_callback = handler;
			break;
		case PIT_1:
			PIT_CH1_callback = handler;
			break;
		case PIT_2:
			PIT_CH2_callback = handler;
			break;
		case PIT_3:
			PIT_CH3_callback = handler;
			break;
		default:
			break;
		}
}/*PIT_callback_init */

bool_t return_PIT0_status_flag(void)
{
	return pit_status_flag;
}

void clear_pit0_status_flag(void)
{
	pit_status_flag = FALSE;
}

bool_t return_PIT1_status_flag(void)
{
	return pit1_status_flag;
}

void clear_pit1_status_flag(void)
{
	pit1_status_flag = FALSE;
}
