#include "main.h"

#include "cv.h"
#include "flash.h"
#include "tim.h"


typedef struct {
	uint16_t signature;
	uint16_t checksum;
	uint8_t *cvptr;
} CVBlock_t;

//const CVBlock_t __attribute__((section (".cv"))) CVBlock;

// "Supported" CV means it can be updated (written to)
// "Not supported" CV can be read from flash

//const uint32_t __attribute__((section (".cv"))) supportedCV = SUPPORTEDCV(1) | SUPPORTEDCV(3);

//
//// Bit mask for CV1..CV32
//const uint32_t __attribute__((section (".rodata"))) supportedCV_1_32 =
//		SUPPORTEDCV(1) | SUPPORTEDCV(3);
//// Bit mask for CV33..CV64
//const uint32_t __attribute__((section (".rodata"))) supportedCV_33_64 = 0;
//// Bit mask for CV65..CV96
//const uint32_t __attribute__((section (".rodata"))) supportedCV_65_96 = 0;



// Read-Only CVs: 7 and 8

// Default CV values in pairs (CV, Value)
const uint8_t __attribute__((section (".rodata"))) defaultCVs [] = {
		CV1_PRIMARY_ADDRESS, 		3,						// Primary Address
		CV2_VSTART, 				0,						// Vstart
		CV3_ACCELERATION_RATE, 		0,						// Acceleration Rate
		CV4_DECELERATION_RATE, 		0,						// Deceleration Rate
		CV5_VHIGH, 					0,						// Vhigh
		CV6_VMID, 					0, 						// Vmid
		CV7_MANUFACTURER_VERSION, 	0,						// Manufacturer Version
		CV8_MANUFACTURER_ID, 		23,						// Manufacturer ID
		CV9_PWM_PERIOD, 			0,						// Total PWM Period

//		CV11_PACKET_TIMEOUT,		0,						// Packet Timeout

		CV17_EXT_ADDRESS_MSB,		0,
		CV18_EXT_ADDRESS_LSB,		3,

		CV29_CONFIGURATION,			CV29_DEFAULT_VALUE,		// Configuration

		CV33_FORWARD_HEADLIGHT,		1,
		CV34_REVERSE_HEADLIGHT,		2,
		CV35_FUNCTION_1,			4,
		CV36_FUNCTION_2,			8,
		CV37_FUNCTION_3,			16,

		CV38_FUNCTION_4,			4,

		CV49_FL,					0,
		CV50_RL,					0,
		CV51_F1,					0,
		CV52_F2,					0,
		CV53_F3,					0,
		CV54_F4,					0,

		CV64_KICK_TIME,				0,						// Kick time
		CV65_KICK_START,			0,						// Kick

		0, 0		// End
};



uint8_t IsCVSupported (uint16_t cvnum) {
uint8_t *addr = CVTOADDR(cvnum);

	return (*addr == cvnum);
}


uint8_t ReadCV (uint16_t cvnum) {
uint8_t cv = 0;
uint8_t *addr = CVTOADDR(cvnum);
//uint8_t *addr = (FLASH_CV_ADDR + FLASH_CV_OFFSET + ((cvnum - 1) * 2));

	if (*addr == cvnum) {
		cv = *(addr + 1); //defaultCVs [7*2 + 1];		// get ManufID
	}

	return cv;
}

uint16_t ReadDoubleCV (uint16_t cvnum) {
uint16_t cv;

	cv = ReadCV (cvnum) << 8;
	cv += ReadCV (cvnum + 1);

	return cv;
}


void UpdateCV (uint16_t cvnum, uint8_t val) {
uint8_t *addr;
uint8_t cvBlock [256];
uint8_t i;


	addr = CVTOADDR(cvnum);

	// Supported CVs have their number written along with value at corresponding address
	if (*addr == cvnum) {
		// Only update value if it is different from the one stored in flash
		if (*(addr + 1) != val) {

//			__HAL_TIM_DISABLE_IT(&htim14, TIM_IT_CC1);


			// Copy CV block from flash to RAM
			// Update RAM
			// Calculate checksum, if necessary
			// Write CV block from RAM to flash

			addr = (uint8_t *)FLASH_CV_ADDR;

			for (i = 0; i < 255; i ++) {
				cvBlock [i] = *addr ++;
			}


			cvBlock [4 + (cvnum * 2) + 1] = val;	// Write new CV value after CV num


			FlashUnlock ();

			FlashErasePage (FLASH_CV_ADDR);

			// copy cvBlock to Flash
			for (i = 0; i < 254; i += 2) {

				HAL_IWDG_Refresh (&hiwdg);

				FlashWriteHalfWord (FLASH_CV_ADDR + i,
									((uint16_t)(cvBlock [i + 1]) << 8) + cvBlock [i]
									);
			}

			FlashLock ();

//			__HAL_TIM_DISABLE_IT(&htim14, TIM_IT_CC1);

		}
	}



}
