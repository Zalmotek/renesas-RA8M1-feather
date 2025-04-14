# Zalmotek RA8M1 Feather Flash Memory Example

This project demonstrates Flash memory operations on the Zalmotek RA8M1 Feather board powered by Renesas RA8M1 MCU.

## Overview

The project enables reading, writing, and erasing operations on external flash memory using OSPI (Octal Serial Peripheral Interface). It utilizes Zalmotek's RA8M1 Feather board with Renesas RA8M1 MCU to communicate with a Micron MT25QL128ABA1EW7 flash device through SPI protocol mode.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- External Micron MT25QL128ABA1EW7 flash memory
- USB connection cable
- J-Link debugger (for programming and debugging)

## Software Requirements

- e² studio IDE
- Renesas FSP (Flexible Software Package)
- J-Link RTT Viewer
- GCC ARM Compiler

## Features

- Flash memory identification and verification
- SPI protocol mode (1S-1S-1S) operation
- Read, write, and erase operations on flash memory
- Interactive menu-driven interface via J-Link RTT Viewer
- Error handling and reporting

## Code Functionality

The main application:
- Initializes the OSPI interface for communication with external flash memory
- Sets up a timer to measure OSPI operation performance
- Reads the flash device ID for verification (manufacturer, memory interface type, density)
- Provides a menu-driven interface for selecting operations
- Supports three main operations: write, read, and erase
- Performs error handling for all operations
- Maps flash device memory to RA8M1 address space for direct access

## Getting Started

### Setup

1. Connect the Zalmotek RA8M1 Feather board to your computer
2. Open e² studio IDE and import the project
3. Build the project using the GCC ARM compiler
4. Program the MCU using J-Link debugger
5. Open J-Link RTT Viewer to interact with the application

### Configuration

The application is configured to communicate with the flash device using the SPI protocol mode:

```c
// Example OSPI configuration for SPI mode
#define OSPI_B_CS1_START_ADDRESS            (0x90000000)
#define OSPI_B_APP_ADDRESS(sector_no)       ((uint8_t *)(OSPI_B_CS1_START_ADDRESS + ((sector_no) * OSPI_B_SECTOR_SIZE_4K)))
```

## Project Structure

- `src/hal_entry.c`: Main application entry point with initialization and menu handling
- `src/ospi_b_ep.c`: OSPI interface implementation for flash operations
- `src/ospi_b_ep.h`: Header file with constants and function prototypes for OSPI operations
- `src/ospi_b_commands.c`: Implementation of flash memory command sequences
- `src/ospi_b_commands.h`: Header file with flash command definitions
- `src/common_utils.h`: Utility functions and macros
- `src/SEGGER_RTT/`: RTT communication library for debug output

## License

Refer to the Renesas Electronics Corporation license information in the source files.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 