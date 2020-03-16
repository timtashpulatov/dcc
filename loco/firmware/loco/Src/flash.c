#include "main.h"

#include "flash.h"

// On STM32F030x4 devices, the main Flash memory space is limited to sector 3

void FlashInitCVs (void) {

uint16_t *addr = FLASH_CV_ADDR;	// last 1K

	if (0xAA55 == *addr) {
		// Signature found
	} else {
		/* (1) Wait till no operation is on going */
		/* (2) Check that the Flash is unlocked */
		/* (3) Perform unlock sequence */
		while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (1) */
		{
		/* For robust implementation, add here time-out management */
		}

		if ((FLASH->CR & FLASH_CR_LOCK) != 0 ) /* (2) */
		{
			FLASH->KEYR = FLASH_FKEY1; /* (3) */
			FLASH->KEYR = FLASH_FKEY2;

			FLASH->CR |= FLASH_CR_PG;
			*(uint16_t *)(addr) = 0xaa55;

			while ((FLASH->SR & FLASH_SR_BSY) != 0);

			if ((FLASH->SR & FLASH_SR_EOP) != 0) {
				FLASH->SR |= FLASH_SR_EOP;
			} else {
				// error
			}
			FLASH->CR &= ~FLASH_CR_PG;

		}
	}

}
