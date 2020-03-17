#include "main.h"

#include "cv.h"


#define SUPPORTEDCV(x) (1<<(x-1))

#define SUPPORTED_CV_1					0b00000001
#define SUPPORTED_CV_2					0b00000010
#define SUPPORTED_CV_3					0b00000100
#define SUPPORTED_CV_4					0b00001000
// etc






// "Supported" CV means it can be updated (written to)
// "Not supported" CV can be read from flash

const uint32_t __attribute__((section (".cv"))) supportedCV = SUPPORTEDCV(1) | SUPPORTEDCV(3);  //SUPPORTED_CV_1 | SUPPORTED_CV_2 | SUPPORTED_CV_3;


uint8_t ReadCV (uint16_t addr) {
uint8_t cv = 0;

//	cv = *((uint8_t *)0x08003c00);

	cv = supportedCV;


	return cv;
}

void UpdateCV (uint16_t addr, uint8_t val) {

}
