# Zalmotek RA8M1 Feather UV Sensor Interface

An I2C communication implementation for Zalmotek RA8M1 Feather board to interface with the AS7331 UV sensor, powered by Renesas.

## Overview

This project demonstrates I2C (IIC) master communication between the Zalmotek RA8M1 Feather board and the AS7331 UV sensor. It continuously reads UV light data (UVA, UVB, UVC) and temperature from the sensor using the I2C protocol, and displays the readings through serial output.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- AS7331 UV sensor breakout board
- Connecting wires
- USB cable for power and programming

## Software Requirements

- e² studio IDE
- Renesas FSP (Flexible Software Package)
- Serial terminal program (for viewing results)

## Features

- I2C master communication implementation
- AS7331 UV sensor configuration and data reading
- Continuous monitoring of UVA, UVB, and UVC radiation levels
- Temperature measurement
- Data conversion to physical units (μW/cm²)

## Code Functionality

The main application:
- Initializes the AS7331 UV sensor over I2C
- Configures sensor measurement parameters (mode, clock, gain, timing)
- Continuously polls sensor status to check for new data
- Reads UV and temperature measurements when available
- Converts raw values to physical units using calibration coefficients
- Outputs formatted data via serial communication

## Getting Started

### Setup

1. Connect the AS7331 sensor to the RA8M1 Feather board's I2C pins
2. Import the project into e² studio
3. Build the project
4. Flash the program to the RA8M1 Feather board
5. Open a serial terminal to view the UV and temperature readings

### Configuration

Sensor parameters can be modified by adjusting these variables:

```c
// Specify sensor parameters
MMODE   mmode = AS7331_CONT_MODE;  // Measurement mode
CCLK    cclk  = AS7331_1024;       // Clock frequency (MHz)
uint8_t gain = 8;                  // Sensor gain (0-11)
uint8_t timeMs = 9;                // Integration time (2^timeMs ms)
```

## Project Structure

- `src/hal_entry.cpp`: Main application entry point and UV sensor handling
- `src/as7331.h`: AS7331 UV sensor driver implementation
- `src/i2c_dev.h`: I2C communication interface
- `src/Wire.h`: I2C protocol utilities
- `src/SEGGER_RTT/`: Debug output libraries

## License

[License information]

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 