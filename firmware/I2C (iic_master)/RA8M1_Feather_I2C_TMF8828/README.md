# Zalmotek RA8M1 Feather I2C TMF8828

A Zalmotek distance measurement application using TMF8828 ToF sensor with Renesas RA8M1 microcontroller via I2C interface.

## Overview

This project demonstrates I2C communication between the Zalmotek RA8M1 Feather board and the TMF8828 Time-of-Flight (ToF) sensor. The application collects 8x8 distance matrices from the sensor and outputs the readings through the debug console. This provides accurate 3D spatial awareness using Renesas RA8M1 technology.

## Hardware Requirements

- Zalmotek RA8M1 Feather board 
- TMF8828 Time-of-Flight (ToF) sensor
- Connecting wires for I2C communication
- USB cable for programming and serial output

## Software Requirements

- Renesas e² studio IDE
- FSP (Flexible Software Package) version 5.3.0 or later
- GCC ARM Embedded toolchain (12.2.1)
- Terminal program for viewing serial output

## Features

- I2C communication with TMF8828 Time-of-Flight sensor
- 8x8 distance matrix data collection and visualization
- Factory calibration support for the ToF sensor
- Multiple configuration options for sensor sampling periods
- Real-time distance measurement output

## Code Functionality

The main application:
- Initializes the I2C communication with the TMF8828 sensor (I2C address 0x41)
- Performs factory calibration of the sensor for accurate measurements
- Sets up the sensor with appropriate configuration (period and iterations)
- Continuously collects 8x8 distance data from the sensor
- Processes and outputs two 8x8 distance matrices (Object0 and Object1)
- Updates readings every 500ms for real-time monitoring

## Getting Started

### Setup

1. Connect the TMF8828 sensor to the Zalmotek RA8M1 Feather board's I2C pins
2. Import the project into e² studio
3. Build the project using the GCC ARM Embedded toolchain
4. Flash the program to the RA8M1 Feather board
5. Open a terminal program to view the sensor readings (baudrate: 115200)

### Configuration

The TMF8828 sensor can be configured with different sampling periods as shown in the code:

```c
// for each configuration specifiy a period in milli-seconds
const uint16_t configPeriod[3] = {132, 264, 528};

// for each configuration specify the number of Kilo Iterations (Kilo = 1024)
const uint16_t configKiloIter[3] = {250, 500, 1000};
```

## Project Structure

- `src/hal_entry.cpp`: Main application entry point and sensor reading logic
- `src/tmf8828.h`: TMF8828 sensor class implementation
- `src/tmf8828_sensor.h`: Core sensor functionality and communication
- `src/tmf8828_calib.h`: Calibration routines for the sensor
- `src/i2c_op.h`: I2C communication functions
- `src/Wire.h`: Wire library for I2C communication
- `src/SEGGER_RTT/`: Debug output functionality

## License

Copyright © 2023 Zalmotek

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 