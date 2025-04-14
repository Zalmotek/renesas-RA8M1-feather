# Zalmotek RA8M1 Feather Digital Pins

A digital pins demonstration project for the Zalmotek RA8M1 Feather board powered by Renesas microcontroller.

## Overview

This project demonstrates digital pin control on the Zalmotek RA8M1 Feather board featuring Renesas RA8M1 microcontroller. It sequentially blinks 8 LED pins to showcase the GPIO functionality and Arduino compatibility of the platform.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- LEDs (can be connected to pins 5, 6, 9, 10, 11, 12, 13, 14)
- USB cable for power and programming

## Software Requirements

- e² studio IDE
- FSP (Flexible Software Package)
- GCC ARM compiler
- Arduino core libraries

## Features

- Sequential LED blinking on 8 different GPIO pins
- Arduino-compatible code syntax
- USB serial output for pin status
- Configurable blink timing

## Code Functionality

The main application:
- Initializes 8 GPIO pins (5, 6, 9, 10, 11, 12, 13, 14) as outputs
- Sequentially turns each LED on and off with configurable delay
- Sends current pin number to serial output for monitoring
- Runs in an infinite loop with a 1-second pause between sequences

## Getting Started

### Setup

1. Clone or download the project repository
2. Open the project in e² studio IDE
3. Connect the Zalmotek RA8M1 Feather board to your computer
4. Build the project
5. Flash the program to the board

### Configuration

You can modify the LED pin configuration and timing in the main_thread_entry.cpp file:

```cpp
// Array of LED pins
int ledPins[] = {5, 6, 9, 10, 11, 12, 13, 14};
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); 
int blinkDelay = 500; // Delay in milliseconds
```

## Project Structure

- `src/main_thread_entry.cpp`: Contains the main application code for LED control
- `src/handler_thread_entry.cpp`: Handles initialization and system setup
- `src/hal_entry.cpp`: Entry point for the hardware abstraction layer
- `src/common_utils.h`: Common utility functions and definitions

## License

Proprietary - Zalmotek

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 