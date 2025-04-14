# Zalmotek RA8M1 Feather USB UART

A USB UART communication example for the Zalmotek RA8M1 Feather board powered by Renesas RA8M1.

## Overview

This project demonstrates how to implement USB UART communication on the Zalmotek RA8M1 Feather board using the Renesas RA8M1 microcontroller. It allows for bidirectional serial communication between the board and a host computer through the USB interface.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- USB cable (Type-A to micro-USB)
- Host computer with USB port

## Software Requirements

- e² studio IDE
- FSP (Flexible Software Package)
- Terminal emulator (e.g., PuTTY, TeraTerm, or Serial Monitor)

## Features

- USB CDC (Communications Device Class) implementation
- Bidirectional data transfer
- Simple command-response interface
- Automatic USB detection on host computer

## Code Functionality

The main application:
- Initializes the USB peripheral for CDC operation
- Sets up the UART communication parameters
- Handles data reception from the host computer
- Processes commands and sends responses
- Demonstrates proper USB connection management

## Getting Started

### Setup

1. Connect the Zalmotek RA8M1 Feather board to your computer using a USB cable
2. Open the project in e² studio
3. Build and flash the project to the board
4. Open a terminal emulator and connect to the board's COM port
5. Send commands to interact with the board

### Configuration

The USB UART module is configured with the following settings:

```c
// USB CDC configuration
#define LINE_CODING_LENGTH (0x07U)
#define LINE_CODING_RATE   (115200U)
#define LINE_CODING_FORMAT (0x00U)
#define LINE_CODING_PARITY (0x00U)
#define LINE_CODING_DATA   (0x08U)
```

## Project Structure

- `src/`: Contains the source code files
- `src/hal_entry.c`: Main application entry point
- `src/usb/`: USB UART implementation files
- `configuration.xml`: Project configuration file

## License

This project is licensed under the MIT License.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 