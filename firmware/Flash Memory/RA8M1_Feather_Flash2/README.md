# Zalmotek RA8M1 Feather Flash Memory Interface

A flash memory interface example for Zalmotek RA8M1 Feather board powered by Renesas RA8M1 microcontroller.

## Overview

This project demonstrates the implementation of SPI flash memory operations using Renesas OSPI (Octal Serial Peripheral Interface) on the Zalmotek RA8M1 Feather board. It provides functionality for reading, writing, and erasing operations to external flash memory using the MT25QL128ABA1EW7 flash device.

## Hardware Requirements

- Zalmotek RA8M1 Feather board 
- MT25QL128ABA1EW7 flash memory device
- J-Link debugger
- USB cable

## Software Requirements

- Renesas e² Studio IDE
- Renesas FSP (Flexible Software Package)
- J-Link RTT Viewer
- GCC ARM Compiler

## Features

- SPI protocol mode (1S-1S-1S) flash memory operations
- Read device ID operation
- Write data to flash memory
- Read data from flash memory
- Erase flash memory sectors (4K)
- Timing measurement for operations

## Code Functionality

The main application:
- Initializes OSPI driver module and flash device in SPI mode
- Reads and displays the flash device ID
- Provides a menu-driven interface via RTT Viewer
- Performs write, read, and erase operations based on user input
- Uses OSPI channel B for communication with the flash device
- Implements proper error handling

## Getting Started

### Setup

1. Connect the Zalmotek RA8M1 Feather board to your computer via USB
2. Open the project in Renesas e² Studio IDE
3. Build the project
4. Flash the binary to the RA8M1 Feather board
5. Open J-Link RTT Viewer to interact with the application

### Configuration

The application allows configuration through the menu-driven interface. Example code for SPI mode initialization:

```c
/* Initialize OSPI driver module and Flash device in SPI mode */
err = ospi_b_init();
```

## Project Structure

- `src/hal_entry.c`: Main application entry point and menu handling
- `src/ospi_b_commands.h`: Flash memory device commands and parameters
- `src/ospi_b_commands.c`: Implementation of flash memory command functions
- `src/ospi_b_ep.h`: Project-specific definitions and function declarations
- `src/ospi_b_ep.c`: Implementation of flash memory operations
- `src/common_utils.h`: Utility functions and macros

## License

This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 