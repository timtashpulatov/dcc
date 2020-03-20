#include "main.h"

#include "cv.h"
#include "motor.h"
#include "functions.h"



static volatile uint8_t CurrentSpeed = 0;		// In speed steps (14, 28, or 128)
static volatile uint8_t TargetSpeed = 0;

static volatile uint8_t CurrentDir = 0;			// Forward

static volatile uint8_t Rate = 0;
static volatile uint32_t motorUpdateTime;

static volatile uint16_t VStart;
static volatile uint8_t SpeedStep;


void MotorInit (void) {
uint16_t VHigh;

	MotorStopPWM ();
	MotorSetAccelDecelRate ();
	MotorRestartUpdateTimer ();

	VHigh = ReadCV (CV5_VHIGH);
	if (0 == VHigh)
		VHigh = 255;
	VHigh = VHigh * 4;

	VStart = ReadCV (CV2_VSTART) * 4;

	SpeedStep = (VHigh - VStart) / 127;
}


// Must be called periodically
void MotorUpdateSpeed (void) {
	if (HAL_GetTick () >= motorUpdateTime) {

		MotorRestartUpdateTimer ();

		if (Rate) {
			Rate --;
		} else {

			MotorSetAccelDecelRate ();

			if (CurrentSpeed < TargetSpeed) {
				CurrentSpeed ++;
				MotorSetPWM (MotorSpeedToDuty ());
			} else if (CurrentSpeed > TargetSpeed) {
				CurrentSpeed --;
				MotorSetPWM (MotorSpeedToDuty ());
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
		TIM3->CCR1 = pwm;
	} else {
		TIM3->CCR1 = 0;
		TIM3->CCR2 = pwm;
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
				SetFrontLight (CurrentDir ? 1 : 0);
				SetRearLight (CurrentDir ? 0 : 1);

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

	// Step = (CV5 (Vhigh) - CV2 (Vstart)) / 128
	// Duty = CV2 (Vstart) + Speed * Step

//	return (CurrentSpeed << 3);
	return (VStart + CurrentSpeed * SpeedStep);
}


