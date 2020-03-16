#include "main.h"

#include "flash.h"

// On STM32F030x4 devices, the main Flash memory space is limited to sector 3

const ConfigBlock configBlock = {0xfeedbeef};
