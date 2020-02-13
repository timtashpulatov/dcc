#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define LED1_Pin 		GPIO_PIN_13
#define LED1_Port 	GPIOC

#define LED2_Pin		GPIO_PIN_14
#define LED2_Port		GPIOC

#define LED3_Pin		GPIO_PIN_15
#define LED3_Port		GPIOC


void MX_GPIO_Init(void);



#ifdef __cplusplus
}
#endif
#endif
