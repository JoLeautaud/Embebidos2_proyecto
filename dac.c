/*
 * dac.c
 *
 *  Created on: 26 sep. 2023
 *      Author: gabyd
 */

#include "dac.h"

void DAC0_init(void)
{
	dac_config_t g_dac_config;

	DAC_GetDefaultConfig(&g_dac_config);

	DAC_Init(DAC0, &g_dac_config);

	DAC_Enable(DAC0, 1);

}
