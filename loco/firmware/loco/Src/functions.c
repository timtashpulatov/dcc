#include "main.h"
#include "functions.h"
#include "motor.h"

static volatile uint8_t Functions1;	// bit 0 - F0(f), 1 - F0(r), 2 - F1 etc
static volatile uint8_t Functions2;

static volatile uint32_t funcUpdateTime;

void SetFunctions1 (uint8_t funcs) {

	Functions1 = funcs;

	// If Bit 1 of CV#29 has a value of one (1), then bit 4 controls function FL,
	// otherwise bit 4 has no meaning.


	HAL_GPIO_WritePin (F1_GPIO_Port, F1_Pin, (funcs & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (F2_GPIO_Port, F2_Pin, (funcs & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_GPIO_WritePin (F3_GPIO_Port, F3_Pin, (funcs & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_GPIO_WritePin (F4_GPIO_Port, F4_Pin, (funcs & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

//	if (funcs & 0x08) {
//		ServiceModeBaseAck ();
//	}
//

}

void SetFunctions2 (uint8_t funcs) {
	Functions2 = funcs;
}

void InitFunctions (void) {
	funcUpdateTime = 0;
}


// Must be called periodically
void UpdateFunctions (void) {
	if (HAL_GetTick () >= funcUpdateTime) {
		funcUpdateTime = HAL_GetTick () + FUNCUPDATEPERIOD;

		// Process functions

		// TEST

		if (GetCurrentDir () == 0) {
			SetFrontLight (1);
			SetRearLight (0);
		} else {
			SetFrontLight (0);
			SetRearLight (1);
		}

		// TEST


	}
}



void SetFrontLight (uint8_t on) {
	HAL_GPIO_WritePin (FL_GPIO_Port, FL_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void SetRearLight (uint8_t on) {
	HAL_GPIO_WritePin (RL_GPIO_Port, RL_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/* MERG Lighting Effects

 	 CV49	FL
 	 CV50	RL
 	 CV51	F1
 	 CV52	F2
 	 CV53	F3
 	 CV54	F4

 	 Effect Bits

 	 0		Dim
 	 1		Strobe
 	 2		MARS
 	 3		Reverse
 	 4		Forward
 	 5		QSec Phase A
 	 6		QSec Phase B
 	 7		SRC (Speed Related Counter)


 */
