# Zalmotek RA8M1 Feather Serial Communication

A serial communication implementation for the Zalmotek RA8M1 Feather board powered by Renesas microcontroller.

## Overview

This project provides a Serial compatibility layer for the RA8M1 Feather development board, enabling easy UART communication. It utilizes the SCI_B UART peripheral from the Renesas RA8M1 microcontroller and implements an Arduino-like Serial interface.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- USB cable for power and programming
- Serial terminal program on PC (optional for testing)

## Software Requirements

- Renesas e² studio IDE
- FSP (Flexible Software Package)
- GCC ARM compiler

## Features

- Arduino-style Serial communication API
- Configurable baud rate settings
- Buffered input and output
- Interrupt-driven UART operation
- Simple print and println methods for data output

## Code Functionality

The main application:
- Initializes UART communication at 115200 baud rate
- Continuously outputs numerical values and text messages
- Utilizes a compatibility layer that provides Arduino-like Serial functions
- Implements a circular buffer for efficient data management
- Uses interrupts for non-blocking operation

## Getting Started

### Setup

1. Clone or download this repository
2. Open the project in Renesas e² studio
3. Build the project for the RA8M1 Feather board
4. Program the board using the debugger
5. Open a serial terminal program on your computer (115200 baud, 8-N-1)

### Configuration

The serial port is initialized with 115200 baud in the main application:

```c
Serial.begin(115200);

while(1){
    Serial.println(10);
    Serial.print((uint8_t*)"Meow\n");
}
```

## Project Structure

- `src/hal_entry.cpp`: Main application entry point
- `src/SerialCompatibility.h`: Implementation of the Serial compatibility layer
- `configuration.xml`: Project configuration file
- `.settings/`: IDE configuration files
- `script/`: Build scripts

## License

[License information]

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 