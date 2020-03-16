#ifndef __FLASH_H_
#define __FLASH_H_

typedef struct {
    uint32_t deviceType;
} ConfigBlock;


extern const ConfigBlock configBlock; // Provided by linker


#endif
