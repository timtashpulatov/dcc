#include "main.h"
#include "tim.h"
#include "adc.h"

#include "loco.h"
#include "nmra.h"
#include "flash.h"
#include "cv.h"
#include "motor.h"
#include "functions.h"

#define USE_WATCHDOG



IWDG_HandleTypeDef hiwdg;

/* USER CODE BEGIN PV */

volatile uint32_t now;
volatile uint32_t motorUpdateTime;
volatile uint32_t functionsUpdateTime;


//  extern DCC_MSG Msg;
extern volatile DccRx_t DccRx;

DCC_MSG Msg;


void SystemClock_Config (void);
static void MX_GPIO_Init (void);
static void MX_IWDG_Init (void);

int main(void) {
  
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();


  /* Initialize all configured peripherals */
  MX_GPIO_Init ();
  MX_DMA_Init ();
  MX_ADC_Init ();
#ifdef USE_WATCHDOG
  MX_IWDG_Init ();
#endif
  MX_TIM3_Init ();
  MX_TIM14_Init ();
  TIM16_Init ();


  /* USER CODE BEGIN 2 */


  // Flash stuff

  FlashCheckCVs ();


  HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_2);

  HAL_TIM_IC_Start_IT (&htim14, TIM_CHANNEL_1);

  // Support stopping timers in debug
//  __HAL_RCC_DBGMCU_CLK_ENABLE();


  // Setup soft timers
  now = HAL_GetTick ();
//  functionsUpdateTime = now + FUNCTIONSUPDATEINTERVAL;

  MotorInit ();
  FunctionsInit ();
  ServiceModeInit ();

  // Start ADC

//  HAL_ADC_Start (&hadc);


  while (1)
  {
#ifdef USE_WATCHDOG
	  HAL_IWDG_Refresh (&hiwdg);
#endif

//	  HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_SET);
//	  HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_RESET);


	  if (DccRx.DataReady) {
//		  	  HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_SET);
//		  	  HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_RESET);

		   Msg = DccRx.PacketCopy;

		   uint8_t xorValue = 0 ;

		   for (uint8_t i = 0; i < DccRx.PacketCopy.Size; i++)
		         xorValue ^= DccRx.PacketCopy.Data [i];
		   if (xorValue) {

//		         Checksum error

		       } else {
						if ((Msg.Data [0] != 0xff)) {	// && (Msg.Size != 2)) {
//						if (1) {
//							HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_SET);

							Decode ();

//							HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_RESET);
						}
		       }

		  DccRx.DataReady = 0;
//		  HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_RESET);
	  }

	  // Periodic tasks
	  now = HAL_GetTick ();

	  MotorUpdateSpeed ();

	  UpdateFunctions ();

	  // etc


  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14
                              |RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}


/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}



/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, F1_Pin|F2_Pin|RL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : F1_Pin F2_Pin RL_Pin */
  GPIO_InitStruct.Pin = F1_Pin|F2_Pin|RL_Pin | Debug_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : FL_Pin */
  GPIO_InitStruct.Pin = FL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FL_GPIO_Port, &GPIO_InitStruct);

  // Debug pin
//  GPIO_InitStruct.Pin = Debug_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(Debug_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
