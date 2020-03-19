#ifndef __CV_H__
#define __CV_H__

//#define SUPPORTEDCV(x) (1<<(x-1))

#define CV1_PRIMARY_ADDRESS			1
#define CV2_VSTART					2
#define CV3_ACCELERATION_RATE		3
#define CV4_DECELERATION_RATE		4
#define CV5_VHIGH					5
#define CV6_VMID					6
#define CV7_MANUFACTURER_VERSION	7
#define CV8_MANUFACTURER_ID			8
#define CV9_PWM_PERIOD				9

#define CV29_CONFIGURATION			29


#define CV29_DEFAULT_VALUE	2

extern const uint8_t defaultCVs [];


uint8_t ReadCV (uint16_t cvnum);

#endif
