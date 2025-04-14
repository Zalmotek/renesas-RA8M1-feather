# Zalmotek RA8M1 Feather I2C AS7343

I2C communication example between Zalmotek RA8M1 Feather and AS7343 Spectral Color Sensor powered by Renesas RA8M1 microcontroller.

## Overview

This project demonstrates I2C master communication between the Zalmotek RA8M1 Feather board and the AS7343 Spectral Color Sensor. The application initializes the sensor, configures its settings, and reads spectral data using the I2C peripheral on the RA8M1 microcontroller. The data is then processed and output via UART.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- AS7343 Spectral Color Sensor
- Connecting wires
- USB cable for power and communication

## Software Requirements

- e² studio IDE
- RA FSP (Flexible Software Package)
- J-Link debugger software
- Terminal software (for viewing UART output)

## Features

- I2C master mode communication
- AS7343 sensor initialization and configuration
- Reading and processing of spectral color data
- UART output of sensor readings
- Error handling for I2C communication

## Code Functionality

The main application:
- Initializes the RA8M1's I2C peripheral in master mode
- Configures the SDA and SCL pins (P401 and P400)
- Sets up the AS7343 sensor with appropriate registers
- Implements read/write functions for I2C communication
- Handles sensor data collection at regular intervals
- Processes and formats data before sending via UART
- Implements error detection and recovery for I2C transactions

## Getting Started

### Setup

1. Connect the AS7343 sensor to the RA8M1 Feather board (SDA to P401, SCL to P400)
2. Open the project in e² studio IDE
3. Build the project using the RA FSP
4. Connect the board to your computer via USB
5. Flash the program to the RA8M1 Feather board
6. Open a terminal program to view the UART output (115200 baud)

### Configuration

The I2C communication is configured with the following settings:

```c
// I2C Master configuration
#define I2C_MASTER_RATE        400000      // 400kHz Fast mode
#define AS7343_SLAVE_ADDRESS   0x39        // 7-bit I2C address of AS7343
```

## Project Structure

- `hal_entry.c`: Main application entry point and I2C initialization
- `as7343.c/h`: AS7343 sensor driver implementation
- `i2c_master.c/h`: I2C communication wrapper functions
- `common/`: Common utilities and definitions
- `configuration/`: Project configuration files

## License

[License information]

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 