#include "main.h"
#include "loco.h"
#include "nmra.h"

void Decode () {
uint8_t speed = 0;

	switch (Msg.Data [1] & INSTR_TYPE_BIT_MASK) {
		case INSTR_DECODER_AND_CONSIST_CONTROL:
			break;

		case INSTR_ADVANCED_OPERATION:
			// 001CCCCC 0 DDDDDDDD
				/* CCCCC = 11111: 128 Speed Step Control - Instruction "11111" is used to send
				one of 126 Digital Decoder speed steps. The subsequent single byte shall define
				speed and direction with bit 7 being direction ("1" is forward and "0" is reverse)
				and the remaining bits used to indicate speed.
				The most significant speed bit is bit 6.

				A data-byte value of U0000000 is used for stop,
				and a data-byte value of U0000001 is used for emergency stop.

				This allows up to 126 speed steps.
				*/

			// Directional lighting
			HAL_GPIO_WritePin (FL_GPIO_Port, FL_Pin,
					Msg.Data [2] & INSTR_DIRECTION_BIT_MASK ? GPIO_PIN_SET : GPIO_PIN_RESET);

			HAL_GPIO_WritePin (FL_GPIO_Port, RL_Pin,
					Msg.Data [2] & INSTR_DIRECTION_BIT_MASK ? GPIO_PIN_RESET : GPIO_PIN_SET);

			// Speed
			speed = Msg.Data [2] & INSTR_SPEED_BIT_MASK;
			if (1 == speed) {
				// Emergency stop
				speed = 0;
			}
			TIM3->CCR1 = speed;	// TODO accelerate/deccelerate

			break;

		case INSTR_SPEED_DIR_REVERSE:
			// 010DDDDD

//			TIM3->CCR1 = Msg.Data [1] & INSTR_SPEED_BIT_MASK;


			break;

		case INSTR_SPEED_DIR_FORWARD:
			// 011DDDDD
			break;

		case INSTR_FUNCTION_GROUP_1:
			// 100DDDDD - FL and F1-F4
			// If Bit 1 of CV#29 has a value of one (1), then bit 4 controls function FL,
			// otherwise bit 4 has no meaning.
			break;

		case INSTR_FUNCTION_GROUP_2:
			// 101SDDDD - F5-F12
			break;

		case INSTR_FEATURE_EXPANSION:
			break;

		case INSTR_CV_ACCESS:
			// 1111CCCC 0 DDDDDDDD - short form
			// 1110CCVV 0 VVVVVVVV 0 DDDDDDDD - long form
			break;

		default:
			break;
	}

}
