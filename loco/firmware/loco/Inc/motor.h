#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTORUPDATEPERIOD		8	//7	// ms
#define KICK_SPEED_THRESHOLD	1	// Enable kick start for speed steps under 5
#define KICK_TIME				10	// Kick time in milliseconds

void MotorRestartUpdateTimer (void);
void MotorSetSpeed (uint8_t newSpeed, uint8_t dir);
void MotorInit (void);
uint16_t MotorSpeedToDuty (void);
void MotorSetPWM (uint16_t pwm);
void MotorStopPWM (void);
void MotorSetAccelDecelRate (void);
uint8_t GetCurrentDir (void);
void MotorUpdateSpeed (void);
void UpdateMotorControlParameters (void);

#endif
