 

   * [Table of Contents](#table-of-contents)
      * [1. I2S vs PCM](#1-i2s-vs-pcm)
         * [I2S](#i2s)
         * [PCM](#pcm)
         * [Variants in Digital Audio Transmission](#variants-in-digital-audio-transmission)
            * [TDM](#tdm)
            * [RPI-TDM ?](#rpi-tdm-)
      * [2. Digital Audio Clocking](#2-digital-audio-clocking)
         * [Master Clock](#master-clock)
         * [DAI Clocks](#dai-clocks)
         * [BCLK Calculation](#bclk-calculation)






Table of Contents
=================

I2S - Inter-IC Sound Bus
=========================

## 1. I2S vs PCM

**_I2S is interface, PCM is a digital representation of an audio signal._**

### I2S
I2S is a standard protocol for transmitting two channels (stereo)
Pulse Code Modulated digital data over a 3-wire serial bus.

I2S, also known as Inter-IC Sound, Integrated Interchip Sound, or IIS, is an 
electrical serial businterface standard used for connecting digital audio
devices together. It is used to communicate PCM audio data between integrated
circuits in an electronic device

I2S is a electrical serial interface used to transmit PCM data from one device to another.
It is used to communicate PCM audio data between integrated circuits in an electronic device.

The interface has a line used to delineate frames called the frame clock, a line for marking 
individual bits called the bit clock and 1 or more lines for the data.

### PCM
PCM is a digital representation of an audio signal. It can be stored in memory or written 
on paper or whatever. 
An example of a 16-bit PCM audio sample might be something like 0x0152.

Raw or pulse code modulated (PCM) is the most basic form of data that converters use to 
translate a digital value to an analog signal. The audio samples are represented as twos 
complement signed data.

Wave files (.wav) are usually Little Endian if they were recorded on a PC.

PCM Most converters use a frame sync signal to signify the beginning of a new sample of audio data. 
These converters are usually associated with mono or single channel converters. 
The frame sync pulse frequency is usually the sample rate in the single channel converter.
The frame sync signal determines when the next audio sample is to be transferred between the 
controller and the converter

[Reference](http://cache.freescale.com/files/microcontrollers/doc/app_note/AN2979.pdf)

### Variants in Digital Audio Transmission

There are many different standards for transmitting digital audio data from one place to another.
Some formats, such as I2S, TDM, and PDM are typically used for inter-IC communication on the
same PC board. Others, such as

S/PDIF and Ethernet AVB are primarily used for data connections from one PCB to another through cabling

While I2S format is the most commonly used, there are other variants of this same 3-wire configuration,
such as **_left-justified, right-justified, and PCM modes_**. 

These differ from I2S by the position of the data word in the frame, the polarity
of the clocks, or the number of bit clock cycles in each frame. 

#### TDM

Some ICs support multiple I2S data inputs or outputs using a common clock, but this obviously
increases the number of pins necessary to transfer the data. Time division multiplexed (TDM)
formats are used when more than two channels of data are to be transferred on a single data line.

A TDM data stream can carry as many as sixteen channels of data and has a data/clock configuration
similar to that of I2S.

Each channel of data uses a slot on the data bus that is 1/Nth the width of the frame,
where N is the number of channels being transferred. For practical purposes, N is usually
rounded up to the nearest power-of-two (2, 4, 8, or 16) and any additional channels are left empty.
A TDM frame clock is often implemented as a single bit-wide pulse, rather than I2S’s 50% duty cycle clock

_TDM is commonly used for a system with multiple sources feeding one input, or one source driving
multiple devices_. In the former case, each TDM source shares a common data bus.

Digital Audio Signal Chain
![Traditional Audio Signal Chain](../images/audio-signal-chain.png?raw=true)

[Common Inter-IC Digital
Interfaces for Audio Data
Transfer](http://www.analog.com/media/en/technical-documentation/technical-articles/MS-2275.pdf)

#### RPI-TDM, Possible ?

> Koalo's Idea

> Standard I2S can only transmit two channels per direction (i.e. stereo). 
> There are other standards (e.g. TDM) that can transmit more channels, but there is no support for them by the Raspberry Pi.
> I want to have in the best case four input channels and six output channels. 
  There are not even many audio codecs (ICs) that support that much channels.
   
  My idea is connect multiple codecs to the CPLD. 
  They will transmit their data via I2S and the CPLD should output this as a single I2S stream. 
  For the hardware of the Raspberry Pi this seems like a stereo audio stream with a high sampling rate, 
  but the software will then distribute the stereo signal into the multiple channels again.

  [Reference - TDM on RPi](https://github.com/Guzunty/Pi/issues/11)    
  [Koalo's Github Page](https://github.com/koalo)

## 2. Digital Audio Clocking

The below text describes the audio clocking terms in ASoC and digital audio in
general. Note: Audio clocking can be complex!

### Master Clock

Every audio subsystem is driven by a master clock (sometimes referred to as MCLK
or SYSCLK). This audio master clock can be derived from a number of sources
(e.g. crystal, PLL, CPU clock) and is responsible for producing the correct
audio playback and capture sample rates.

Some master clocks (e.g. PLLs and CPU based clocks) are configurable in that
their speed can be altered by software (depending on the system use and to save
power). Other master clocks are fixed at a set frequency (i.e. crystals).

`On my TLV it is derived from a 12 MHz on-board crystal`

###	DAI Clocks

I2S is a common 4 wire DAI. The Digital Audio Interface is usually driven by a
Bit Clock (often referred to as BCLK). This clock is used to drive the digital
audio data across the link between the codec and CPU.

The DAI also has a frame clock to signal the start of each audio frame. This
clock is sometimes referred to as LRC (left right clock) or FRAME. This clock
runs at exactly the sample rate (LRC = Rate).

Bit Clock can be generated as follows:-

	BCLK = MCLK / x

	 or

	BCLK = LRC * x

	 or

	BCLK = LRC * Channels * Word Size

This relationship depends on the codec or SoC CPU in particular. In general
it is best to configure BCLK to the lowest possible speed (depending on your
rate, number of channels and word size) to save on power.

It is also desirable to use the codec (if possible) to drive (or master) the
audio clocks as it usually gives more accurate sample rates than the CPU.

### BCLK Calculation

The device which generates appropriate bit clock (CLK) and word clock (WC) signals on the bus is called
master, whereas other devices which accept CLK and WC as inputs are all slaves. 

The serialized audio signal transmitting device (which may or may not be the master device) places the data on the bus in
synchronization with the CLK and WC signal from the master. Serializers are capable of receiving the clocking signals to
act as I2S slave and the Deserializer device regenerates all of the necessary clocking signals to act as I2S master.
	
**Audio Interface Frequencies**

|Sample Rate/WCLK (kHz) 	| I2S Data Word Size (bits)  	|  I2S_CLK/BCLK (MHz) |
|---------------------- 	|:--------------------------:	|--------------------:|
| 192                    	| 16                   			| 6.144     		  |
| 32                     	| 24                   			| 1.536     		  |
| 44.1                   	| 24                   			| 2.117     		  |
| 48                     	| 24                   			| 2.304     		  |
| 96                     	| 24                   			| 4.608     		  |
| 192                    	| 24                   			| 9.216     		  |
| 32                     	| 32                   			| 2.048     		  |
| 44.1                   	| 32                   			| 2.822     		  |
| 48                     	| 32                   			| 3.072     		  |
| 96                     	| 32                   			| 6.144     		  |
| 192                    	| 32                   			| 12.288    		  |

**Bit Rate Calculation**

I2S data lines (PCM streams) have two basic properties that determine their fidelity to the original analog
signal i.e., sampling rate (fS) and number of bits per sample (M). Hence, I2S_CLK is decided by the bit
rate (BR) required to transport a digital audio signal, which can be calculated as follows:
	
		BR = MNfs
	
		M = Bit depth per sample (example: M=16 for 16-bits per channel)
		N = number of channels (example: N=2 for standard I2S stereo format)
		fs = sampling rate (example: fs=48kHz)

**Wikipedia**

The bit clock pulses once for each discrete bit of data on the data lines. The bit clock
frequency is the product of the sample rate, the number of bits per channel and the number of channels. 

So, for example, CD Audio with a sample frequency of 44.1 kHz, with 16 bits of precision
and two channels (stereo) has a bit clock frequency of:

		44.1 kHz × 16 × 2 = 1.4112 MHz

The word select clock lets the device know whether channel 1 or channel 2 is currently being sent,
since I²S allows two channels to be sent on the same data line. 
For stereo material, the I²S specification states that left audio is transmitted on the low cycle
of the word select clock and the right channel is transmitted on the high cycle. 
The word select clock is a 50% duty-cycle signal that has the same frequency as the sample frequency.		

