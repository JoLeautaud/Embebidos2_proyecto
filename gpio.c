/*
 * gpio.c
 *
 *  Created on: 11 oct. 2023
 *      Author: gabyd
 */


#include "gpio.h"

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

volatile static bool_t g_reverse_pressed_flag = FALSE;
volatile static bool_t g_blink_pressed_flag = FALSE;
volatile static bool_t g_right_pressed_flag = FALSE;
volatile static bool_t g_left_pressed_flag = FALSE;

static void (*gpio_A_callback)(uint32_t flag) = 0;
static void (*gpio_B_callback)(uint32_t flag) = 0;
static void (*gpio_C_callback)(uint32_t flag) = 0;
static void (*gpio_D_callback)(uint32_t flag) = 0;
static void (*gpio_E_callback)(uint32_t flag) = 0;

uint8_t irq_AFLAG = FALSE;

void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flag))
{
	switch(gpio)
	{
		case GPIO_A:
			gpio_A_callback = handler;
			break;
		case GPIO_B:
			gpio_B_callback = handler;
			break;
		case GPIO_C:
			gpio_C_callback = handler;
			break;
		case GPIO_D:
			gpio_D_callback = handler;
			break;
		default:
			gpio_E_callback = handler;
			break;
	}
}




void GPIO_init(void)
{
	gpio_pin_config_t gpio_input_config = {
			        kGPIO_DigitalInput,
			        0,
			    };

	gpio_pin_config_t gpio_output_config = {
			        kGPIO_DigitalOutput,
			        1,
			    };

	const port_pin_config_t button_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);
	CLOCK_EnableClock(kCLOCK_PortC);

	//control para Motores
	GPIO_PinInit(GPIOC, 1u, &gpio_output_config);
	PORT_SetPinMux(PORTC, 1u, kPORT_MuxAlt4);

	//control para Servomotor
	GPIO_PinInit(GPIOC, 3u, &gpio_output_config);
	PORT_SetPinMux(PORTC, 3u, kPORT_MuxAlt4);

	//Boton para Reversa
	GPIO_PinInit(GPIOC, REVERSE, &gpio_input_config);
	PORT_SetPinConfig(PORTC, REVERSE, &button_config);
	PORT_SetPinInterruptConfig(PORTC, REVERSE, kPORT_InterruptFallingEdge);

	//Botones de Direccionales
	GPIO_PinInit(GPIOC, RIGHT, &gpio_input_config);
	PORT_SetPinConfig(PORTC, RIGHT, &button_config);
	PORT_SetPinInterruptConfig(PORTC, RIGHT, kPORT_InterruptFallingEdge);

	GPIO_PinInit(GPIOC, LEFT, &gpio_input_config);
	PORT_SetPinConfig(PORTC, LEFT, &button_config);
	PORT_SetPinInterruptConfig(PORTC, LEFT, kPORT_InterruptFallingEdge);

	//Boton para Intermitentes
	GPIO_PinInit(GPIOC, BLINK, &gpio_input_config);
	PORT_SetPinConfig(PORTC, BLINK, &button_config);
	PORT_SetPinInterruptConfig(PORTC, BLINK, kPORT_InterruptFallingEdge);

	//LED izquirdo
	PORT_SetPinMux(PORTC, LED_R, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, LED_R, &gpio_output_config);
	//LED derecho
	PORT_SetPinMux(PORTC, LED_L, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, LED_L, &gpio_output_config);

}


/*getters for each sound called*/

bool_t get_reverse_pressed_flag(void){
	return g_reverse_pressed_flag;
}

bool_t get_blink_pressed_flag(void){
	return g_blink_pressed_flag;
}

bool_t get_right_pressed_flag(void){
	return g_right_pressed_flag;
}

bool_t get_left_pressed_flag(void){
	return g_left_pressed_flag;
}


/*setters for each sound called*/

void set_reverse_pressed_flag(bool_t value){
	g_reverse_pressed_flag= value;
}

void set_blink_pressed_flag(bool_t value){
	g_blink_pressed_flag = value;
}

void set_right_pressed_flag(bool_t value){
	g_right_pressed_flag = value;
}

void set_left_pressed_flag(bool_t value){
	g_left_pressed_flag = value;
}

/* Change frequency */
void PORTA_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_PortGetInterruptFlags(GPIOA);
	if(gpio_A_callback)
	{
		gpio_A_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOA, 0xFFFF);
}

/* Change signal */
void PORTB_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_PortGetInterruptFlags(GPIOB);
	if(gpio_B_callback)
	{
		gpio_B_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOB, 0xFFFF);
}

void PORTC_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_PortGetInterruptFlags(GPIOC);
	if(irq_status & (1 << REVERSE)){
		set_reverse_pressed_flag(TRUE);
	}

	if(irq_status & 1 << BLINK){
		set_blink_pressed_flag(TRUE);
	}

	if(irq_status & 1 << RIGHT){
		set_right_pressed_flag(TRUE);
	}

	if(irq_status & 1 << LEFT){
		set_left_pressed_flag(TRUE);
	}
	if(gpio_C_callback)
	{
		gpio_C_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOC, irq_status);
}

void PORTD_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_PortGetInterruptFlags(GPIOD);

	if(gpio_D_callback)
	{
		gpio_D_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOD, 0xFFFF);
}

void PORTE_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_PortGetInterruptFlags(GPIOE);
	if(gpio_E_callback)
	{
		gpio_E_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOE, 0xFFFF);
}

uint8_t return_portA_irq_status(void)
{
	return irq_AFLAG;
}

void clear_AFLAG(void)
{
	irq_AFLAG = FALSE;
}
