#include "main.h"

#include "cv.h"
#include "motor.h"



static volatile uint8_t CurrentSpeed = 0;		// In speed steps (14, 28, or 128)
static volatile uint8_t TargetSpeed = 0;

static volatile uint8_t CurrentDir = 0;			// Forward

static volatile uint8_t Rate = 0;
static volatile uint32_t motorUpdateTime;


void MotorInit (void) {
	MotorStopPWM ();
	MotorSetAccelDecelRate ();
	MotorRestartUpdateTimer ();
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

void MotorSetPWM (uint8_t pwm) {
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
		Rate = 7 * ReadCV (CV4_DECELERATION_RATE);
	} else {
		Rate = 7 * ReadCV (CV3_ACCELERATION_RATE);
	}
}

void MotorRestartUpdateTimer (void) {
	motorUpdateTime = HAL_GetTick () + MOTORUPDATEPERIOD;
}


uint8_t MotorSpeedToDuty (void) {
	return (CurrentSpeed << 1);
}


