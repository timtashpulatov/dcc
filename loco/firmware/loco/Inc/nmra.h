#ifndef __NMRA_H__
#define __NMRA_H__


/* 	000 Decoder and Consist Control Instruction
	001 Advanced Operation Instructions
	010 Speed and Direction Instruction for reverse operation
	011 Speed and Direction Instruction for forward operation
	100 Function Group One Instruction
	101 Function Group Two Instruction
	110 Future Expansion
	111 Configuration Variable Access Instruction
*/

#define INSTR_TYPE_BIT_MASK					0b11100000

#define INSTR_DECODER_AND_CONSIST_CONTROL	0b00000000
#define INSTR_ADVANCED_OPERATION			0b00100000
#define INSTR_SPEED_DIR_REVERSE				0b01000000
#define INSTR_SPEED_DIR_FORWARD				0b01100000
#define INSTR_FUNCTION_GROUP_1				0b10000000
#define INSTR_FUNCTION_GROUP_2				0b10100000
#define INSTR_FEATURE_EXPANSION				0b11000000
#define INSTR_CV_ACCESS						0b11100000

#define INSTR_DIRECTION_BIT_MASK			0b10000000
#define INSTR_SPEED_BIT_MASK				0b01111111

extern DCC_MSG Msg;

void Decode ();



#endif
