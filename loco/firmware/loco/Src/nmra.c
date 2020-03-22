#include "main.h"
#include "loco.h"
#include "nmra.h"
#include "motor.h"
#include "functions.h"
#include "cv.h"

typedef enum {
	INACTIVE = 0,
	POSSIBLE = 1,			// upon Reset packet reception
	ACTIVE = 2				// upon Reset packet + service mode instruction reception
} ServiceMode_t;

static ServiceMode_t ServiceMode;

// 78 00 e8 - read CV1 in Direct mode

void Decode () {
uint8_t speed = 0;
uint8_t dir = 0;
uint8_t cv;
uint8_t val;

	if ((3 == Msg.Size) && ((0 == Msg.Data [0]) && (0 == Msg.Data [1]))) {
		// Reset packet
		MotorInit ();
		FunctionsInit ();

		if (INACTIVE == ServiceMode) {
			ServiceMode = POSSIBLE;
		} else if (POSSIBLE == ServiceMode) {
			ServiceMode = ACTIVE;
		}
	}

	else

	switch (ServiceMode) {

	case POSSIBLE:
		// Wait for another Service Mode instruction or Reset packet
		break;

	case ACTIVE:
		if ((4 == Msg.Size) && (0b01110000 == (Msg.Data [0] & 0b11110000))) {

			cv = Msg.Data [1] + 1;

			if (IsCVSupported (cv)) {

				val = ReadCV (cv);

				if ((Msg.Data [0] & 0b11111100) == 0b01110100) {
					// Verify Byte
					if (val == Msg.Data [2])
						ServiceModeBaseAck ();
				}

				if ((Msg.Data [0] & 0b11111100) == 0b01111100) {
					// Write Byte
					UpdateCV (cv, Msg.Data [2]);
					ServiceModeBaseAck ();
				}

				if ((Msg.Data [0] & 0b11111100) == 0b01111000) {
					// Bit Manipulation
					// 0 011110AA 0 AAAAAAAA 0 111KDBBB 0 EEEEEEEE 1

					uint8_t bitPos = Msg.Data [2] & 7;
					uint8_t workingBit = (Msg.Data [2] & 8) ? 1 : 0;

					if ((Msg.Data [2]) & 0b00010000) {
						// Write bit
						if (workingBit) {
							val |= (1 << bitPos);
						} else {
							val &= ~(1 << bitPos);
						}
						UpdateCV (cv, val);
						ServiceModeBaseAck ();

					} else {
						// Verify bit
						if (((val >> bitPos) & 1) == workingBit)
							ServiceModeBaseAck ();
					}
				}

			}

		}
		break;

	case INACTIVE:
	default:
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

				SetFunctions1 (Msg.Data [2]);

				break;

			case INSTR_FUNCTION_GROUP_2:
				// 101SDDDD - F5-F12

				SetFunctions2 (Msg.Data [2]);

				break;

			case INSTR_FEATURE_EXPANSION:
				break;

			case INSTR_CV_ACCESS:
				// 1111CCCC 0 DDDDDDDD - short form TODO

				if (5 == Msg.Size) {
					// 1110CCVV 0 VVVVVVVV 0 DDDDDDDD - long form
					cv = Msg.Data [2] + 1;		// TODO support 10-bit CVs (CV512+)
					if (IsCVSupported (cv)) {
						val = Msg.Data [3];
						switch (Msg.Data [1] & 0b00001100) {
						case 0b00000100:	// Verify byte
							break;
						case 0b00001100:	// Write byte
							UpdateCV (cv, val);
							break;
						case 0b00001000:	// Bit manipulation
							// TODO 111CDBBB C=1 Write bit
							break;
						default: break;
						}
					}
				}
				break;

			default:
				break;
		}
		break;
	}

}




// Service mode


// Basic Acknowledgement - at least 60 mA for 6 ms +/-1 ms

void ServiceModeBaseAck (void) {


	SetFrontLight (1);
	SetRearLight (1);

	MotorSetPWM (255*8);

	HAL_Delay (6);

	MotorStopPWM ();

	// TODO additional delay to make blink more noticeable

	SetFrontLight (0);
	SetRearLight (0);
}

void ServiceModeInit (void) {
	ServiceMode = INACTIVE;
}

/*
	Hard-Reset-Cycle - A hard reset (see RP-9.2.1), followed by 10 idle or reset packets. This sequence is used when a
	Command Station/Programmer desires to return the decoder to its initial predefined state.

	Page-Preset-Instruction - A packet sequence sent to guarantee the contents of the page register. The instruction
	sequence is (long-preamble 0 01111101 0 00000001 0 01111100 1)

	Decoder Factory Reset - long-preamble 0 01111111 0 00001000 0 01110111 1

*/
