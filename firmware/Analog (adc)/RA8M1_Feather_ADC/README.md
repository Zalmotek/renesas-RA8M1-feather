# Zalmotek RA8M1 Feather ADC

A demonstration project for analog-to-digital conversion using the Zalmotek RA8M1 Feather board powered by Renesas RA8M1 microcontroller.

## Overview

This project demonstrates ADC functionality on the Zalmotek RA8M1 Feather board featuring Renesas RA8M1 microcontroller. It configures and utilizes the ADC peripheral to read analog values, convert them to digital values, and output the results through the SEGGER RTT interface.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- USB cable for power and programming
- Analog signal source (optional, for testing with external signals)

## Software Requirements

- e² studio IDE
- FSP (Flexible Software Package)
- SEGGER J-Link software
- SEGGER RTT Viewer

## Features

- Multiple ADC channel support
- Continuous or single-shot sampling modes
- Window comparator functionality
- Real-time conversion data visualization through RTT
- Voltage calculation and display

## Code Functionality

The main application:
- Initializes the ADC module with proper configuration
- Sets up RTT communication for user interface
- Handles ADC scanning start/stop based on user input
- Reads ADC data from multiple channels and calculates voltage values
- Displays converted values through RTT communication
- Implements window comparator functionality with event callback

## Getting Started

### Setup

1. Connect the Zalmotek RA8M1 Feather board to your computer using a USB cable
2. Open the project in e² studio IDE
3. Build the project
4. Flash the program to the RA8M1 Feather board
5. Open SEGGER RTT Viewer to interact with the application

### Configuration

The ADC is configured for multiple channels with the following settings:

```c
// ADC configuration in FSP configurator
// Resolution: 12-bit
// Conversion speed: High speed
// Reference voltage: Internal reference
```

## Project Structure

- `src/hal_entry.c`: Main application entry point and control logic
- `src/adc_ep.c`: ADC-specific implementation and functionality
- `src/adc_ep.h`: Header file containing ADC-related definitions
- `src/SEGGER_RTT/`: RTT communication implementation files
- `src/common_utils.h`: Common utility functions and definitions

## License

This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 