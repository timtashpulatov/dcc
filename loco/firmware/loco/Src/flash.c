#include "main.h"

#include "flash.h"
#include "cv.h"

// On STM32F030x4 devices, the main Flash memory space is limited to sector 3


void FlashCheckCVs (void) {
uint16_t *addr = FLASH_CV_ADDR;	// last 1K

	if (*addr != SIGNATURE) {
//	if (1) {
		// No signature found
		// Erase page and fill with default values

		FlashUnlock ();

		FlashErasePage (FLASH_CV_ADDR);

		FlashInitCVs ();

		FlashLock ();

	}
}

void FlashUnlock (void) {
	while ((FLASH->SR & FLASH_SR_BSY) != 0) {
		/* For robust implementation, add here time-out management */
	};

	if ((FLASH->CR & FLASH_CR_LOCK) != 0 ) {
		FLASH->KEYR = FLASH_FKEY1;
		FLASH->KEYR = FLASH_FKEY2;
	}
}

void FlashLock (void) {
	if (0 == (FLASH->CR & FLASH_CR_LOCK)) {
		FLASH->CR |= FLASH_CR_LOCK;
	}
}


void FlashErasePage (uint32_t page_addr) {
	FLASH->CR |= FLASH_CR_PER;

	FLASH->AR = page_addr;
	FLASH->CR |= FLASH_CR_STRT;
	while ((FLASH->SR & FLASH_SR_BSY) != 0) {
		/* For robust implementation, add here time-out management */
	};

	if ((FLASH->SR & FLASH_SR_EOP) != 0) {
		FLASH->SR |= FLASH_SR_EOP;
	} else {
		/* Manage the error cases */
	}

	FLASH->CR &= ~FLASH_CR_PER;
}


void FlashWriteHalfWord (uint32_t addr, uint16_t val) {
	FLASH->CR |= FLASH_CR_PG;

	*(uint16_t *)(addr) = val;

	while ((FLASH->SR & FLASH_SR_BSY) != 0);

	if ((FLASH->SR & FLASH_SR_EOP) != 0) {
		FLASH->SR |= FLASH_SR_EOP;
	} else {
		// error
	}

	FLASH->CR &= ~FLASH_CR_PG;
}

void FlashInitCVs (void) {
uint8_t i;
uint32_t addr;

	while ((FLASH->SR & FLASH_SR_BSY) != 0) {
		/* For robust implementation, add here time-out management */
	};

	FlashWriteHalfWord (FLASH_CV_ADDR, SIGNATURE);

	addr = FLASH_CV_ADDR + 4;	// skip signature and checksum
	i = 0;
	while (1) {
		if (0 == defaultCVs [i])
			break;
		else {
			FlashWriteHalfWord (addr + (defaultCVs [i]) * 2,
					((uint16_t)(defaultCVs [i + 1]) << 8) + defaultCVs [i]
					);
		}
		i += 2;
	}
}
