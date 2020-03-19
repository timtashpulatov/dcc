#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTORUPDATEPERIOD	7	// ms

void MotorRestartUpdateTimer (void);
void MotorSetSpeed (uint8_t newSpeed, uint8_t dir);
void MotorInit (void);
uint8_t MotorSpeedToDuty (void);

#endif
