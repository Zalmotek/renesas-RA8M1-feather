# Zalmotek RA8M1 Feather Blink

A simple LED blinking example for the Zalmotek RA8M1 Feather board powered by Renesas microcontroller.

## Overview

This project demonstrates the basic functionality of the Zalmotek RA8M1 Feather board by blinking an onboard LED connected to pin BSP_IO_PORT_01_PIN_15. It utilizes the Renesas RA8M1 microcontroller to toggle the LED state at regular intervals and outputs status messages through the debug console.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- USB cable for power and programming

## Software Requirements

- e² studio IDE
- Renesas FSP (Flexible Software Package)
- Renesas RA MCU toolchain

## Features

- Simple LED blinking demonstration
- 500ms toggle interval
- Debug console output
- Low power consumption

## Code Functionality

The main application:
- Initializes the IOPORT for GPIO access
- Configures BSP_IO_PORT_01_PIN_15 for LED control
- Toggles the LED state every 500ms
- Outputs status messages ("LED ON"/"LED OFF") to the debug console
- Runs in an infinite loop

## Getting Started

### Setup

1. Connect the Zalmotek RA8M1 Feather board to your computer via USB
2. Open the project in e² studio IDE
3. Build the project using the Renesas RA MCU toolchain
4. Flash the compiled program to the board
5. The onboard LED should begin blinking with a 500ms interval

### Configuration

The LED pin and timing can be modified in the hal_entry.cpp file:

```c
// Change LED pin
R_BSP_PinWrite(BSP_IO_PORT_01_PIN_15, pin_level);

// Change blink interval (milliseconds)
R_BSP_SoftwareDelay(500, bsp_delay_units);
```

## Project Structure

- `src/hal_entry.cpp`: Main application code with LED blinking logic
- `src/common_utils.h`: Utility functions and macros
- `src/SEGGER_RTT/`: Debug output library
- `configuration.xml`: Project configuration file

## License

[License information]

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 