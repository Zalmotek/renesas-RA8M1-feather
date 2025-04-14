# Zalmotek RA8M1 Feather SD Card

A microSD card interface example for the Zalmotek RA8M1 Feather board powered by Renesas RA8M1 MCU.

## Overview

This project demonstrates how to implement SD card functionality on the Zalmotek RA8M1 Feather board. It provides basic file operations such as reading, writing, and listing files on a microSD card using the SPI interface with Renesas RA8M1 microcontroller.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- MicroSD card
- microSD card adapter (if needed for programming)
- USB cable for board power and programming

## Software Requirements

- Renesas e² studio IDE
- Renesas FSP (Flexible Software Package)
- FreeRTOS (included in the project)
- FatFs file system module

## Features

- MicroSD card initialization and mounting
- File creation and writing operations
- File reading operations
- Directory listing functionality
- Error handling for card operations

## Code Functionality

The main application:
- Initializes the SPI interface for SD card communication
- Mounts the FAT file system on the SD card
- Provides functions for reading and writing files
- Implements directory navigation and file listing
- Handles error conditions and provides status feedback

## Getting Started

### Setup

1. Insert the microSD card into the Zalmotek RA8M1 Feather board
2. Connect the board to your computer using the USB cable
3. Open the project in Renesas e² studio
4. Build and flash the project to the board
5. Monitor the output through the serial interface

### Configuration

The SD card interface uses the SPI protocol with the following configuration:

```c
// SPI configuration for SD card
#define SD_SPI_CHANNEL       0
#define SD_CHIP_SELECT_PIN   PIN_P400  // CS pin
#define SD_MOSI_PIN          PIN_P401  // MOSI
#define SD_MISO_PIN          PIN_P402  // MISO
#define SD_SCK_PIN           PIN_P403  // SCK
```

## Project Structure

- `src/`: Main source code files
- `ra/`: Renesas FSP configuration files
- `ra_cfg/`: User configuration files for the FSP
- `ra_gen/`: Auto-generated configuration code
- `FreeRTOS/`: FreeRTOS kernel files
- `fatfs/`: FatFs file system module

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 