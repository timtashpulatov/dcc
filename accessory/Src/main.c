#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "cv.h"
#include "accessory.h"


void SystemClock_Config(void);

DccRx_t DccRx;
volatile uint32_t bitMax, bitMin, bitVal;

DCC_MSG Msg;

uint32_t when;

uint16_t myAddr;

int main(void)
{


  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  memset (&DccRx, 0, sizeof (DccRx));

  initCV ();
  myAddr = getMyAddr ();

  // Let the fun begin!
  HAL_TIM_IC_Start_IT (&htim2, TIM_CHANNEL_1);
  HAL_TIM_IC_Start (&htim2, TIM_CHANNEL_2);

  when = HAL_GetTick () + HOUSEKEEPING_INTERVAL;

  while (1)
  {

	  // Process DCC packet
	  if (DccRx.DataReady) {

		   Msg = DccRx.PacketCopy;

		   uint8_t xorValue = 0 ;

		   for (uint8_t i = 0; i < DccRx.PacketCopy.Size; i++)
		         xorValue ^= DccRx.PacketCopy.Data [i];
		   if (xorValue) {

//		         Checksum error

		       } else {

		    	   if ((Msg.Data [0] != 0xff) /* && (Msg.Size != 3)*/) {	// Not idle
		    		   uint16_t addr;

		    		   // Accessory Decoder packet
		    		   if ((Msg.Data [0] & 0b11000000) == 0b10000000) {
		    			   if (Msg.Size == 3) {
		    				   // Basic: 10AAAAAA 1AAACDDD
		    				   ProcessBasicAccessoryPacket (&Msg);
		    			   }
		    			   if (Msg.Size == 4) {
				    		   // Extended: 10AAAAAA 0AAA0AA1 000XXXXX (EEEEEEEE)
		    				   ProcessExtendedAccessoryPacket (&Msg);
		    			   }

		    		   }

		    		   // CV access - short form
		    		   // 1111CCCC DDDDDDDD (EEEEEEEE)
		    		   // CV access - long form
		    		   // 1110CCVV VVVVVVVV DDDDDDDD (EEEEEEEE)

		    		   if ((Msg.Data [0] & 0b11110000) == 0b11100000) {
		    			   processCV (&Msg);
		    		   }

		    		   // OPS CV access
		    		   if ((Msg.Size > 5 /* == 6 */) &&
		    			  ((Msg.Data [0] & 0b11000000) == 0b10000000)) {
						   // Basic: 	10AAAAAA 1AAACDDD 1110CCVV VVVVVVVV DDDDDDDD (EEEEEEEE)
						   // Where DDD is used to indicate the output whose CVs are being modified and C=1.
						   // If CDDD= 0000 then the CVs refer to the entire decoder

		    			   // check addr
		    			   addr = (((uint16_t)Msg.Data [0]) & 0x003f) |
		    					   (~(((uint16_t)(Msg.Data [1])) << 2)) & 0x01C0;

		    			   if (addr == myAddr) {
							   if (((Msg.Data [1] & 0b10000000) == 0b10000000)) {
								   // check operation CC
								   updateCV (Msg.Data [3], Msg.Data [4]);

							   }
							   // Extended:	10AAAAAA 0AAA0AA1 1110CCVV VVVVVVVV DDDDDDDD (EEEEEEEE)
							   if ((Msg.Data [1] & 0b10000000) == 0b00000000) {
	//							   processCV (&Msg);
							   }
		    			   }
		    		   }



		    	   }


//		   		if( notifyDccMsg ) 	notifyDccMsg( &Msg );
//
//		           execDccProcessor( &Msg );
		       }
		   DccRx.DataReady = 0;
	  }


	  if (HAL_GetTick () > when) {
		  when = HAL_GetTick () + HOUSEKEEPING_INTERVAL;

		  AccessoryHousekeeping ();
	  }




//	  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	  HAL_Delay (20);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}



void HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef *htim) {
uint8_t DccBitVal;
uint32_t bitMicros;
//uint32_t ch1, ch2;

	bitMicros = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

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
				DccRx.BitCount = 0 ;
			}
			break;

		case WAIT_START_BIT:

			if (DccBitVal) {
				DccRx.BitCount ++;
			} else {
				// we got the startbit
				DccRx.State = WAIT_DATA ;
				DccRx.PacketBuf.Size = 0;
				DccRx.PacketBuf.PreambleBits = 0;
				for(uint8_t i = 0; i< MAX_DCC_MESSAGE_LEN; i++ )
					DccRx.PacketBuf.Data [i] = 0;

				DccRx.PacketBuf.PreambleBits = DccRx.BitCount;
				DccRx.BitCount = 0 ;
				DccRx.TempByte = 0 ;
			}

			break;

		case WAIT_DATA:
			DccRx.BitCount++;
			DccRx.TempByte = (DccRx.TempByte << 1);
			if (DccBitVal)
				DccRx.TempByte |= 1;
			    if (DccRx.BitCount == 8) {
			      if (DccRx.PacketBuf.Size == MAX_DCC_MESSAGE_LEN ) { // Packet is too long - abort
			        DccRx.State = WAIT_PREAMBLE ;
			        DccRx.BitCount = 0 ;
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
