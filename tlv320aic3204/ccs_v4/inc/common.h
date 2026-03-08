
/*********************************************
 * Header for code common to the whole system.
 *********************************************/
 
#ifndef COMMON_
#define COMMON_

#include "stdio.h"

/*********************************************
 * Defines, enums and constants
 *********************************************/ 

// Generate a sine wave on one channel of the headphone 
#define SINE_WAVE
#undef SINE_WAVE

// Unfiltered output ofor a few seconds 
#define PASS_THROUGH

// Use DRC
#define USE_DRC
#undef USE_DRC

// Use AGC
#define USE_AGC
#undef USE_AGC

// Switch the I2S bus into DSP mode (TDM operation)
#define DSP_MODE
#undef DSP_MODE

#define CODEC_1

#define VOLUME_MIN 0xBC
#define VOLUME_MID 0xDC
#define VOLUME_MAX 0xF8

#define MUX_SEL_PINS_B_A_MASK 0x03
#define MOB_MUX_SEL_PINS_B_A 0x03
#define TEL_MUX_SEL_PINS_B_A 0x01
#define PC_MUX_SEL_PINS_B_A  0x00

typedef enum {
	CODEC_ONE,
	CODEC_TWO
} CODEC_SEL;

typedef enum {
	SINGLE_MODE,
	DUAL_MODE
} MODE_SELECT;


typedef enum {
	VOL_UP,
	VOL_DOWN,
	VOL_MIN,
	VOL_MAX
} BEEP_TYPE;

#define DEBUG
#undef DEBUG
#ifdef DEBUG
	#define debug(x) printf x
#else
	#define debug(x) do {} while (0)
#endif


/*********************************************
 * Public functions
 *********************************************/
void c5505_register_irq(void);

#endif /*COMMON_*/
