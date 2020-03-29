#include "main.h"

#include "cv.h"
#include "motor.h"
#include "functions.h"



static volatile uint8_t CurrentSpeed = 0;		// In speed steps (14, 28, or 128)
static volatile uint8_t TargetSpeed = 0;

static volatile uint8_t CurrentDir = 0;			// Forward

static volatile uint8_t Rate = 0;
static volatile uint32_t motorUpdateTime;
static volatile uint32_t kickTime;

static volatile uint16_t VStart;
static volatile uint8_t SpeedStep;
static volatile uint16_t Kick = 0;


void MotorInit (void) {

	MotorStopPWM ();
	MotorSetAccelDecelRate ();
	MotorRestartUpdateTimer ();

	UpdateMotorControlParameters ();

}

static void SetKick (void) {
	if (0 == kickTime) {

		kickTime = ReadCV (CV64_KICK_TIME);

		if (kickTime) {
			Kick = (CurrentSpeed) ? 0 : ReadCV (CV65_KICK_START) * 8;		// TODO parametrize this 8
			kickTime += HAL_GetTick ();
		}
	}
}

// Must be called periodically
void MotorUpdateSpeed (void) {

	// Kick control
	if (HAL_GetTick () >= kickTime) {
		kickTime = 0;

		if (Kick) {
			Kick = 0;
			MotorSetPWM (MotorSpeedToDuty ());
		}
	}


	if (HAL_GetTick () >= motorUpdateTime) {

		MotorRestartUpdateTimer ();

		// Measure Back EMF
		// only when Kick is off
		// - stop PWM
		// - wait (~10us, TBD)
		// - start ADC conversion
		// - poll for EOC
		// - read conversion result, do averaging
		// - start PWM


		// Process speed

		if (CurrentSpeed != TargetSpeed) {

			if (Rate) {
				Rate --;
			} else {

				MotorSetAccelDecelRate ();

				if (CurrentSpeed < TargetSpeed) {
					SetKick ();
					CurrentSpeed ++;
					MotorSetPWM (MotorSpeedToDuty ());
				} else if (CurrentSpeed > TargetSpeed) {
					CurrentSpeed --;
					MotorSetPWM (MotorSpeedToDuty ());
				}
			}
		}
	}
}


void MotorStopPWM (void) {
	TIM3->CCR1 = TIM3->CCR2 = 0;
}

void MotorSetPWM (uint16_t pwm) {
	if (CurrentDir) {
		TIM3->CCR2 = 0;
		TIM3->CCR1 = pwm + Kick;
	} else {
		TIM3->CCR1 = 0;
		TIM3->CCR2 = pwm + Kick;
	}
}


void MotorSetSpeed (uint8_t newSpeed, uint8_t newDir) {

	// Emergency STOP
	if (1 == newSpeed) {
		CurrentSpeed = TargetSpeed = 0;	// newSpeed;
		MotorStopPWM ();
	} else {

		// When changing direction, first bring speed to zero
		if (CurrentDir != newDir) {
			TargetSpeed = 0;

			if (0 == CurrentSpeed) {
				// Reverse and set target speed
				CurrentDir = newDir;
				TargetSpeed = newSpeed;

				// Direction changed
				MotorSetAccelDecelRate ();

				// Update Front/Rear Lights
				// TODO move to Functions processing
//				SetFrontLight (CurrentDir ? 1 : 0);
//				SetRearLight (CurrentDir ? 0 : 1);

			}
		} else {
			// Same direction, possibly different speed
			if (TargetSpeed != newSpeed) {
				TargetSpeed = newSpeed;

				MotorSetAccelDecelRate ();

			}
		}
	}
}

void MotorSetAccelDecelRate (void) {
	if (CurrentDir) {
		Rate = ReadCV (CV4_DECELERATION_RATE);
	} else {
		Rate = ReadCV (CV3_ACCELERATION_RATE);
	}
}

void MotorRestartUpdateTimer (void) {
	motorUpdateTime = HAL_GetTick () + MOTORUPDATEPERIOD;
}


uint16_t MotorSpeedToDuty (void) {
uint16_t duty;
int8_t trim;

	if (CurrentSpeed) {
		trim = ReadCV ((0 == CurrentDir) ? CV66_FORWARD_TRIM : CV95_REVERSE_TRIM);

		// TODO no idea how to apply trim :(

		duty = (CurrentSpeed * SpeedStep) + VStart;
	} else {
		duty = 0;
	}

	return duty;
}

uint8_t GetCurrentDir (void) {
	return CurrentDir;
}

void UpdateMotorControlParameters (void) {
uint16_t VHigh;

	VHigh = ReadCV (CV5_VHIGH);	// TODO use IsSupported ()
	if (0 == VHigh)
		VHigh = 255;
	VHigh = VHigh * 4;

	VStart = ReadCV (CV2_VSTART) * 4; //8;

	SpeedStep = (VHigh - VStart) / 127;
}
