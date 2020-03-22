#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define FUNCUPDATEPERIOD	1		// ms ticks

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t pwm;
} Output_t;


void SetFunctions1 (uint8_t funcs);
void SetFunctions2 (uint8_t funcs);

void SetFrontLight (uint8_t on);
void SetRearLight (uint8_t on);

void UpdateFunctions (void);
void FunctionsInit (void);


#endif
