/*
 * MotorShield.c
 *
 *  Created on: Nov 20, 2023
 *      Author: jorgeleautaud
 */


#include "fsl_gpio.h"
#include "fsl_ftm.h"
#include "fsl_port.h"
#include "FlexTimer.h"

// Define motor control pins
#define MOTOR_A_IN1_PIN 2U  // Replace with the actual pin number connected to L298N IN1
#define MOTOR_A_IN2_PIN 3U  // Replace with the actual pin number connected to L298N IN2
#define MOTOR_B_IN1_PIN 10U  // Replace with the actual pin number connected to L298N IN3
#define MOTOR_B_IN2_PIN 11U  // Replace with the actual pin number connected to L298N IN4

// Define FTM module and channel
#define FTM_MODULE FTM0
#define FTM_CHANNEL kFTM_Chnl_0


/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#ifndef FTM_PWM_ON_LEVEL
#define FTM_PWM_ON_LEVEL kFTM_HighTrue
#endif


/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void initMotorControlPins(void) {
    gpio_pin_config_t motorConfig = {
        kGPIO_DigitalOutput, 1,
    };
	const port_pin_config_t gpio_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);

    // Assign PTC3 to FTM0_CH0
   PORT_SetPinMux(PORTC, 1U, kPORT_MuxAlt4);
   PORT_SetPinMux(PORTC, 3U, kPORT_MuxAlt4);



    // Initialize motor control pins as digital outputs
    GPIO_PinInit(GPIOB, MOTOR_A_IN1_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_A_IN1_PIN, &gpio_config);

    GPIO_PinInit(GPIOB, MOTOR_A_IN2_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_A_IN2_PIN, &gpio_config);

    GPIO_PinInit(GPIOB, MOTOR_B_IN1_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_B_IN1_PIN, &gpio_config);

    GPIO_PinInit(GPIOB, MOTOR_B_IN2_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_B_IN2_PIN, &gpio_config);
}


void moveForward(uint16_t Percent) {
	FlexTimer_updateCHValue(Percent);

    // Motor A
     GPIO_PinWrite(GPIOB, MOTOR_A_IN1_PIN, 1);
     GPIO_PinWrite(GPIOB, MOTOR_A_IN2_PIN, 0);

    // Motor B
    GPIO_PinWrite(GPIOB, MOTOR_B_IN1_PIN, 1);
    GPIO_PinWrite(GPIOB, MOTOR_B_IN2_PIN, 0);
}

void moveBackward(uint16_t Percent) {
	FlexTimer_updateCHValue(Percent);

    // Motor A
    GPIO_PinWrite(GPIOB, MOTOR_A_IN1_PIN, 0);
    GPIO_PinWrite(GPIOB, MOTOR_A_IN2_PIN, 1);


    // Motor B
    GPIO_PinWrite(GPIOB, MOTOR_B_IN1_PIN, 0);
    GPIO_PinWrite(GPIOB, MOTOR_B_IN2_PIN, 1);
}



void stopMotors(void) {

    // Motor A
    GPIO_PinWrite(GPIOB, MOTOR_A_IN1_PIN, 1);
    GPIO_PinWrite(GPIOB, MOTOR_A_IN2_PIN, 1);

    // Motor B
    GPIO_PinWrite(GPIOB, MOTOR_B_IN1_PIN, 1);
    GPIO_PinWrite(GPIOB, MOTOR_B_IN2_PIN, 1);

}
