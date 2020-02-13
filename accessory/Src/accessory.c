#include "main.h"	// rather dcc.h for DCC_MSG and such
#include "gpio.h"
#include "accessory.h"
#include "cv.h"

Function_t functions [NUM_FUNCTIONS] = {
		{LED1_Port, LED1_Pin, 0},
		{LED2_Port, LED2_Pin, 0},
		{LED3_Port, LED3_Pin, 0}
};

void SetAccessoryFunction (uint8_t f, uint8_t on) {
	HAL_GPIO_WritePin (functions [f].Port, functions [f].Pin, GPIO_PIN_RESET);
	functions [f].Expires = cv [3-1];
}

void ProcessBasicAccessoryPacket (DCC_MSG *msg) {
	// 10AAAAAA 1AAACDDD
	SetAccessoryFunction (msg->Data [1] & 0x03, 1);
}

void ProcessExtendedAccessoryPacket (DCC_MSG *msg) {
	// 10AAAAAA 0AAA0AA1 000XXXXX

	   HAL_GPIO_WritePin(LED1_Port, LED1_Pin,
			(msg->Data [2] & 0b00000001) ?
					GPIO_PIN_RESET :
					GPIO_PIN_SET);

	   HAL_GPIO_WritePin(LED2_Port, LED2_Pin,
			(msg->Data [2] & 0b00000010) ?
					GPIO_PIN_SET :
					GPIO_PIN_RESET);

	   HAL_GPIO_WritePin(LED3_Port, LED3_Pin,
			(msg->Data [2] & 0b00000100) ?
					GPIO_PIN_SET :
					GPIO_PIN_RESET);

}



void AccessoryHousekeeping (void) {
uint8_t i;

	for (i = 0; i < NUM_FUNCTIONS; i++) {

		if (functions [i].Expires) {
			functions [i].Expires --;

			if (functions [i].Expires == 0) {
				// Turn function off
				HAL_GPIO_WritePin (functions [i].Port, functions [i].Pin, GPIO_PIN_SET);
			}
		}
	}
}
