#ifndef __LOCO_H__
#define __LOCO_H__


#define MAX_DCC_MESSAGE_LEN     8    	// including XOR-Byte

#define MAX_ONEBITFULL  150	//50+25	//116+10	//200-42          // 146
//#define MAX_PREAMBLE    200             // 146
#define MAX_ONEBITHALF  100     		// 82
#define MIN_ONEBITFULL  100-10	//50-10	//115-15          // 82
//#define MIN_ONEBITHALF  25              // 35
//#define MAX_BITDIFF     25              // 24

typedef struct
{
        uint8_t Size ;
        uint8_t PreambleBits ;
        uint8_t Data [MAX_DCC_MESSAGE_LEN] ;
} DCC_MSG ;

typedef enum
{
  WAIT_PREAMBLE = 0,
  WAIT_START_BIT,
  WAIT_DATA,
  WAIT_END_BIT
}
DccRxWaitState_t;

typedef struct
{
  DccRxWaitState_t  State ;
  uint8_t         DataReady ;
  uint8_t         BitCount ;
  uint8_t         TempByte ;
  DCC_MSG         PacketBuf;
  DCC_MSG         PacketCopy;
} DccRx_t;



#endif
