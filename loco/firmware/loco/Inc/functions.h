#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define FUNCUPDATEPERIOD	1		// ms ticks

void SetFunctions1 (uint8_t funcs);
void SetFunctions2 (uint8_t funcs);

void SetFrontLight (uint8_t on);
void SetRearLight (uint8_t on);

void UpdateFunctions (void);
void FunctionsInit (void);


#endif
