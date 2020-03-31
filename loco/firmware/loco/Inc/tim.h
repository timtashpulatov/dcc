#ifndef __TIM_H__
#define __TIM_H__


#define TIM4_INIT_PERIOD		1000	// 50000

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim14;

void MX_TIM3_Init (void);
void MX_TIM14_Init (void);
void TIM16_Init (void);


#endif
