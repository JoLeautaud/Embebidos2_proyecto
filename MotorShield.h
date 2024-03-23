/*
 * MotorShield.h
 *
 *  Created on: Nov 20, 2023
 *      Author: jorgeleautaud
 */

#ifndef MOTORSHIELD_H_
#define MOTORSHIELD_H_

void initMotorControlPins(void);
void initFTM(void);
void moveForward(uint16_t Percent);
void moveBackward(uint16_t Percent);

#endif /* MOTORSHIELD_H_ */
