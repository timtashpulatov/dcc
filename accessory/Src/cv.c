#include "main.h"
#include "cv.h"
#include "accessory.h"

/*

1110CCVV 0 VVVVVVVV 0 DDDDDDDD

	CC=00 Reserved for future use
	CC=01 Verify byte
	CC=11 Write byte
	CC=10 Bit manipulation
*/


uint8_t cv [CV_MAX_NUM];

void updateCV (uint8_t n, uint8_t data) {
	cv [n] = data;

	// Just in case CV1 and CV9 were changed, update myAddr
	myAddr = getMyAddr ();
}

void processCV (DCC_MSG *msg) {
//uint16_t CV;
//
//	CV = ((msg->Data [0] & 3) | msg->Data [1]) + 1;
//
//	switch (msg->Data [0] & 0b00001100) {
//	case 0b00001100:
//		// Write
//		break;
//	}
}

uint16_t getMyAddr (void) {
	return cv [CV1_DECODER_ADDRESS_LSB] + ((cv [CV9_DECODER_ADDRESS_MSB]) << 8);
}

void initCV (void) {
	cv [CV1_DECODER_ADDRESS_LSB] = CV_DEFAULT_ADDRESS & 0xff;
	cv [CV9_DECODER_ADDRESS_MSB] = CV_DEFAULT_ADDRESS >> 8;
	cv [CV29_ACCESSORY_DECODER_CONFIG] = 0x80;	// TODO

	cv [CV3_F1_TIME_ON] = DEFAULT_FUNCTION_EXPIRES;
	cv [CV4_F1_TIME_ON] = DEFAULT_FUNCTION_EXPIRES;
	cv [CV5_F1_TIME_ON] = DEFAULT_FUNCTION_EXPIRES;
	cv [CV6_F1_TIME_ON] = DEFAULT_FUNCTION_EXPIRES;

}


