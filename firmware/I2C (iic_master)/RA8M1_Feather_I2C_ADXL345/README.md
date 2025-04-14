# Zalmotek RA8M1 Feather I2C ADXL345

Zalmotek RA8M1 Feather demonstration of I2C communication with ADXL345 accelerometer, powered by Renesas microcontroller technology.

## Overview

This project demonstrates how to interface an ADXL345 accelerometer with the Zalmotek RA8M1 Feather board using I2C communication. The application initializes the sensor, reads acceleration data from X, Y, and Z axes every 3 seconds, and outputs the values through the debug console.

## Hardware Requirements

- Zalmotek RA8M1 Feather board 
- ADXL345 accelerometer (PMOD ACL or similar)
- Connection cables
- USB cable for programming and debug output

## Software Requirements

- e² studio IDE
- Renesas FSP (Flexible Software Package)
- J-Link debugger
- Terminal software for viewing debug output

## Features

- I2C master communication with ADXL345 accelerometer
- Initialization and configuration of the accelerometer sensor
- Periodic reading of X, Y, Z acceleration data
- Error handling for initialization and read operations
- Console output of acceleration values

## Code Functionality

The main application:
- Initializes the Renesas RA8M1 microcontroller and required peripherals
- Configures and initializes I2C master communication
- Sets up the ADXL345 accelerometer for data measurement
- Reads X, Y, Z acceleration data every 3 seconds
- Formats and outputs the data to the debug console
- Handles communication errors with appropriate error messages

## Getting Started

### Setup

1. Connect the ADXL345 accelerometer to the RA8M1 Feather I2C pins
2. Open the project in e² studio
3. Build the project using the Renesas FSP configuration
4. Connect the board via USB
5. Download the program to the board
6. Open a terminal program to view the console output

### Configuration

The I2C communication with the accelerometer uses the following configuration:

```c
#define DEVICE_ID_REG           (0x00)
#define DEVICE_SIGNATURE        (0xE5)
#define POWER_CTL_REG           (0x2D)
#define AXIS_DATA               (0x32)
```

## Project Structure

- `src/hal_entry.c`: Main application entry point and control loop
- `src/i2c_sensor.c`: I2C communication with the ADXL345 accelerometer
- `src/i2c_sensor.h`: Header file containing register definitions and function declarations
- `src/common_utils.h`: Utility functions for the application
- `src/SEGGER_RTT/`: Real-Time Terminal (RTT) communication for debug output

## License

This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. Please see the included license disclaimers for more information.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 