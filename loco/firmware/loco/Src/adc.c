#include "main.h"


static uint16_t data;

void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* hadc) {
	data = hadc->Instance->DR;
}
