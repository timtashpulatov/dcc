#ifndef __FLASH_H_
#define __FLASH_H_

#define FLASH_CV_ADDR	0x08003c00
#define SIGNATURE		0x55aa


#define FLASH_FKEY1 0x45670123
#define FLASH_FKEY2 0xCDEF89AB


void FlashCheckCVs (void);
void FlashInitCVs (void);


#endif
