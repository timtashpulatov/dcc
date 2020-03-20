#include "main.h"
#include "loco.h"
#include "tim.h"

volatile DccRx_t DccRx;



volatile uint16_t count0, count1;

//#define NUMDEBUGBITS 20
//uint16_t bits [NUMDEBUGBITS];
//uint8_t bitIndex = 0;

void HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef *htim) {
uint8_t DccBitVal;
uint16_t bitMicros;

//HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_SET);

//__HAL_DBGMCU_FREEZE_TIM3 ();
//__HAL_DBGMCU_FREEZE_TIM14 ();

count0 = count1;
count1 = HAL_TIM_ReadCapturedValue (htim, TIM_CHANNEL_1);

	if (htim->Instance->SR & TIM_SR_CC1OF) {
		htim->Instance->SR = ~(TIM_SR_CC1OF | TIM_SR_CC1IF);
	} else {

		if (count1 > count0) {
			bitMicros = count1 - count0;
		} else {
			bitMicros = TIM4_INIT_PERIOD - count0 + count1;
		}

		// 1 = 116 us (2*58)
		// 0 = 200 us (2*100)

		if (bitMicros > MIN_ONEBITFULL) {

			DccBitVal = (bitMicros < MAX_ONEBITFULL);

			switch (DccRx.State) {

			case WAIT_PREAMBLE:

				if (DccBitVal) {
					DccRx.BitCount++;
					if (DccRx.BitCount > 10) {
						DccRx.State = WAIT_START_BIT;
					}
				} else {
					DccRx.BitCount = 0;
				}
				break;

			case WAIT_START_BIT:

				if (DccBitVal) {
					DccRx.BitCount ++;
				} else {
					// we got the startbit

					// Now, the startbit will be 200 us with correct polarity,
					// and 58+100 with incorrect polarity

					if (bitMicros < MIN_ZEROBIT) {
						// Change polarity and restart detection

						htim->Instance->CCER ^= TIM_CCER_CC1P_Msk;

						DccRx.State = WAIT_PREAMBLE;
						DccRx.BitCount = 0;

					} else {
						DccRx.State = WAIT_DATA;
						DccRx.PacketBuf.Size = 0;
						DccRx.PacketBuf.PreambleBits = 0;
						for (uint8_t i = 0; i < MAX_DCC_MESSAGE_LEN; i++)
							DccRx.PacketBuf.Data [i] = 0;

						DccRx.PacketBuf.PreambleBits = DccRx.BitCount;
						DccRx.BitCount = 0;
						DccRx.TempByte = 0;
					}
				}
				break;

			case WAIT_DATA:
				DccRx.BitCount++;
				DccRx.TempByte = (DccRx.TempByte << 1);
				if (DccBitVal) {
					DccRx.TempByte |= 1;
				}
				if (DccRx.BitCount == 8) {
				  if (DccRx.PacketBuf.Size == MAX_DCC_MESSAGE_LEN) { // Packet is too long - abort
					DccRx.State = WAIT_PREAMBLE;
					DccRx.BitCount = 0;
				  } else {
					DccRx.State = WAIT_END_BIT;
					DccRx.PacketBuf.Data [DccRx.PacketBuf.Size ++] = DccRx.TempByte;
				  }
				}
				break;

			case WAIT_END_BIT:
				DccRx.BitCount ++;
				if (DccBitVal) { // End of packet?
				  DccRx.State = WAIT_PREAMBLE;
				  DccRx.BitCount = 0 ;
				  DccRx.PacketCopy = DccRx.PacketBuf;

				  DccRx.DataReady = 1;

				}
				else  // Get next Byte
				  // KGW - Abort immediately if packet is too long.
				  if (DccRx.PacketBuf.Size == MAX_DCC_MESSAGE_LEN) { // Packet is too long - abort
					DccRx.State = WAIT_PREAMBLE ;
					DccRx.BitCount = 0;
				  } else {
					DccRx.State = WAIT_DATA;
					DccRx.BitCount = 0;
					DccRx.TempByte = 0;
				  }
				break;
			}
		}
	}


//	// Debug bit lengths
//	bits [bitIndex] = bitMicros;
//	bitIndex ++;
//	if (bitIndex >= NUMDEBUGBITS)
//		bitIndex = 0;


//	__HAL_DBGMCU_UNFREEZE_TIM14 ();

//	__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);

//HAL_GPIO_WritePin(FL_GPIO_Port, FL_Pin, GPIO_PIN_RESET);

//	__HAL_DBGMCU_UNFREEZE_TIM3 ();


}

#define PWM_PRESCALER	4 // 4*4		// 12KHz		//48*4	// Results in 1KHz PWM frequency
#define PWM_STEPS		1024 // 256

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = PWM_PRESCALER-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = PWM_STEPS-1;	//	//158-1;	// 500-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;	// (PWM_STEPS/2)-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 48-1;		// TODO 31 good for 64MHz in F103, recalculate for 48MHz of F030
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = TIM4_INIT_PERIOD - 1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
//  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 5;	// 5 microseconds it should be 	// was 0;
  if (HAL_TIM_IC_ConfigChannel(&htim14, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

