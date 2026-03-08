# C5505 + Dual TLV320AIC3204 Interface (CCS v4)

This project targets the **TI C5505 DSP** in **Code Composer Studio v4** and demonstrates interfacing with **two TLV320AIC3204 audio codecs**:

- **Codec 1:** controlled over **I2C**
- **Codec 2:** controlled over **SPI**

## Overview

The firmware initializes and configures two TLV320AIC3204 devices using different control buses on the same DSP platform.
It is intended as a reference for mixed-bus codec control in embedded audio designs.

## Features

- CCSv4-compatible C5505 project structure
- TLV320AIC3204 register programming via I2C
- TLV320AIC3204 register programming via SPI
- Dual-codec initialization flow
- Basic framework for audio path bring-up and validation

## Project Layout

```text
.
├─ src/            # Application source files
├─ include/        # Header files
├─ drivers/        # I2C/SPI and codec driver code
├─ targetConfigs/  # CCS target configuration files
└─ Readme.md
```

## Build and Run

1. Open the project in **Code Composer Studio v4**.
2. Verify the **C5505 target configuration**.
3. Build the project.
4. Load and run on hardware.
5. Monitor codec initialization on both buses (I2C and SPI).

## Notes

- Ensure hardware wiring matches pin assignments used in source.
- Confirm pull-ups and SPI mode settings for stable codec communication.
- Update codec register tables as needed for your audio routing and clock plan.

## Hardware

- TI C5505 DSP platform
- 2 × TLV320AIC3204 codecs
- I2C connection to codec #1
- SPI connection to codec #2
- Proper audio clocks and power rails
