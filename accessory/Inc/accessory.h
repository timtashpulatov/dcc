/*
 * accessory.h
 *
 *  Created on: Feb 9, 2020
 *      Author: tnt23
 */

#ifndef ACCESSORY_H_
#define ACCESSORY_H_

#define NUM_FUNCTIONS	3

#define DEFAULT_FUNCTION_EXPIRES	25	// in 10 milliseconds intervals

typedef struct {
	GPIO_TypeDef *Port;
	uint16_t Pin;
	uint8_t Expires;
} Function_t;


void ProcessBasicAccessoryPacket (DCC_MSG *msg);
void ProcessExtendedAccessoryPacket (DCC_MSG *msg);
void AccessoryHousekeeping (void);
void SetAccessoryFunction (uint8_t f, uint8_t on);

#endif /* ACCESSORY_H_ */
