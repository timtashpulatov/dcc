#ifndef CV_H_
#define CV_H_

/* Accessory decoder Configuration Variables

 	 CV1 (513)	Decoder address LSB					(M)andatory

 	 CV3 (515)	F1 time On							(O)ptional
 	 CV4 (516)	F2 time On							 O
 	 CV5 (517)	F3 time On							 O
 	 CV6 (518)	F4 time On							 O

 	 CV7 (519)	Manufacturer Version Info			 M
 	 CV8 (520)	Manufacturer ID						 M					Write to CV8 resets configuration?
 	 CV9 (521)	Decoder address MSB					 M

 	 CV29 (541)	Accessory decoder configuration		 M


  CV33..CV81 Manufacturer Unique

	CV33
	CV34
	CV35
	CV36
	CV37
	CV38
	CV39
	CV40

	CV41
	CV42
	CV43
	CV44
	CV45
	CV46
	CV47
	CV48


 */

#define CV_DEFAULT_ADDRESS				1
//#define CV_DEFAULT_FUNCTION_TIME		1	// in 10ms intervals for example

#define CV_MAX_NUM						128	// Comment

#define CV1_DECODER_ADDRESS_LSB			0

#define CV3_F1_TIME_ON					2
#define CV4_F1_TIME_ON					3
#define CV5_F1_TIME_ON					4
#define CV6_F1_TIME_ON					5

#define CV7_MANUFACTURER_VERSION_INFO	6
#define CV8_MANUFACTURER_ID				7
#define CV9_DECODER_ADDRESS_MSB			8

#define CV29_ACCESSORY_DECODER_CONFIG	28

extern uint8_t cv [CV_MAX_NUM];



void processCV (DCC_MSG *msg);
void initCV (void);
void updateCV (uint8_t n, uint8_t data);
uint16_t getMyAddr (void);

#endif /* CV_H_ */
