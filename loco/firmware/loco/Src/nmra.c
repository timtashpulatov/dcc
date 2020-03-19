#include "main.h"
#include "loco.h"
#include "nmra.h"
#include "motor.h"

static uint8_t ServiceMode = 0;

void Decode () {
uint8_t speed = 0;
uint8_t dir = 0;

	switch (Msg.Data [1] & INSTR_TYPE_BIT_MASK) {
		case INSTR_DECODER_AND_CONSIST_CONTROL:
			break;

		case INSTR_ADVANCED_OPERATION:
			// 001CCCCC 0 DDDDDDDD

			// The 5-bit sub-instruction CCCCC allows for 32 separate Advanced Operations Sub-Instructions
			switch (Msg.Data [1] & 0b00011111) {
				case ADV_SUBF_128_SPEED_STEP_CONTROL:
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
					dir = Msg.Data [2] & INSTR_DIRECTION_BIT_MASK;

					HAL_GPIO_WritePin (FL_GPIO_Port, FL_Pin,
							dir ? GPIO_PIN_SET : GPIO_PIN_RESET);

					HAL_GPIO_WritePin (RL_GPIO_Port, RL_Pin,
							dir ? GPIO_PIN_RESET : GPIO_PIN_SET);

					// Speed
					speed = Msg.Data [2] & INSTR_SPEED_BIT_MASK;
					MotorSetSpeed (speed, dir);
					break;

				case ADV_SUBF_RESTRICTED_SPEED_STEP:
					break;
				case ADV_SUBF_ANALOG_FUNC_GROUP:
					break;
				default:
					break;
			}

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

			SetFunctions (Msg.Data [2]);

			break;

		case INSTR_FUNCTION_GROUP_2:
			// 101SDDDD - F5-F12
			break;

		case INSTR_FEATURE_EXPANSION:
			break;

		case INSTR_CV_ACCESS:
			// 1111CCCC 0 DDDDDDDD - short form
			// 1110CCVV 0 VVVVVVVV 0 DDDDDDDD - long form

			if (ServiceMode) {

			}

			break;

		default:
			break;
	}

}


void SetFunctions (uint8_t funcs) {
	HAL_GPIO_WritePin (F1_GPIO_Port, F1_Pin, (funcs & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (F2_GPIO_Port, F2_Pin, (funcs & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_GPIO_WritePin (F3_GPIO_Port, F3_Pin, (funcs & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_GPIO_WritePin (F4_GPIO_Port, F4_Pin, (funcs & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


// Service mode

// Basic Acknowledgement - at least 60 mA for 6 ms +/-1 ms

/*
	Hard-Reset-Cycle - A hard reset (see RP-9.2.1), followed by 10 idle or reset packets. This sequence is used when a
	Command Station/Programmer desires to return the decoder to its initial predefined state.

	Page-Preset-Instruction - A packet sequence sent to guarantee the contents of the page register. The instruction
	sequence is (long-preamble 0 01111101 0 00000001 0 01111100 1)

	Decoder Factory Reset - long-preamble 0 01111111 0 00001000 0 01110111 1

*/
