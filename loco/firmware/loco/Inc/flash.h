#ifndef __FLASH_H_
#define __FLASH_H_

#define FLASH_CV_ADDR	((uint8_t *)0x08003c00U)
#define SIGNATURE		0x55aa
#define FLASH_CV_OFFSET	(6U)


#define FLASH_FKEY1 0x45670123
#define FLASH_FKEY2 0xCDEF89AB


void FlashCheckCVs (void);
void FlashInitCVs (void);


#endif
