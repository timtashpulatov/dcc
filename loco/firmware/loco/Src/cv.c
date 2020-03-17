#include "main.h"

#include "cv.h"


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
		1, 3,
		2, 0,		// Vstart
		3, 0,		// Acceleration Rate
		4, 0,		// Deceleration Rate
		5, 0,		// Vhigh
		6, 0, 		// Vmid
		7, 0,		// Manufacturer Version
		8, 23,		// Manufacturer ID
		9, 0,		// Total PWM Period

		29, CV29_DEFAULT_VALUE,	// Configuration

		0, 0		// End
};



uint8_t ReadCV (uint16_t cvnum) {
uint8_t cv = 0;

	cv = defaultCVs [7*2 + 1];		// get ManufID


	return cv;
}

void UpdateCV (uint16_t cvnum, uint8_t val) {

}
