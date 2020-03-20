#ifndef __CV_H__
#define __CV_H__

#define CVTOADDR(x)	((uint8_t *)(FLASH_CV_ADDR + FLASH_CV_OFFSET + ((cvnum - 1) * 2)))

#define CV1_PRIMARY_ADDRESS			1
#define CV2_VSTART					2
#define CV3_ACCELERATION_RATE		3
#define CV4_DECELERATION_RATE		4
#define CV5_VHIGH					5
#define CV6_VMID					6
#define CV7_MANUFACTURER_VERSION	7
#define CV8_MANUFACTURER_ID			8
#define CV9_PWM_PERIOD				9
#define CV10_EMF_FEEDBACK_CUTOUT	10
#define CV11_PACKET_TIMEOUT			11

#define CV17_EXT_ADDRESS_MSB		17
#define CV18_EXT_ADDRESS_LSB		18

#define CV23_ACCEL_ADJUST			23
#define CV24_DECEL_ADJUST			24

#define CV29_CONFIGURATION			29

#define CV65_KICK_START				65


#define CV29_DEFAULT_VALUE	2

extern const uint8_t defaultCVs [];


uint8_t ReadCV (uint16_t cvnum);
uint8_t IsCVSupported (uint16_t cvnum);

#endif
