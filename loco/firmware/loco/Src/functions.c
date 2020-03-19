#include "main.h"
#include "functions.h"

void SetFunctions (uint8_t funcs) {
	HAL_GPIO_WritePin (F1_GPIO_Port, F1_Pin, (funcs & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (F2_GPIO_Port, F2_Pin, (funcs & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_GPIO_WritePin (F3_GPIO_Port, F3_Pin, (funcs & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_GPIO_WritePin (F4_GPIO_Port, F4_Pin, (funcs & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void SetFrontLight (uint8_t on) {
	HAL_GPIO_WritePin (FL_GPIO_Port, FL_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void SetRearLight (uint8_t on) {
	HAL_GPIO_WritePin (RL_GPIO_Port, RL_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

