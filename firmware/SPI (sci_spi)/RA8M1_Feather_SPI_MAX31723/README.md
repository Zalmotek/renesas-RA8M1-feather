# Zalmotek RA8M1 Feather SPI MAX31723

Temperature monitoring application for Zalmotek RA8M1 Feather board using a MAX31723 temperature sensor via SPI.

## Overview

This project demonstrates SPI communication between a Zalmotek RA8M1 Feather board (powered by Renesas RA8M1 microcontroller) and a MAX31723 temperature sensor. It periodically reads temperature values from the sensor and outputs the readings through USB UART. The application uses SCI_SPI on port P4.15 for chip select.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- MAX31723 temperature sensor breakout
- USB cable for power and communication
- Jumper wires for connecting the sensor

## Software Requirements

- Renesas e² studio IDE
- Renesas FSP (Flexible Software Package)
- USB Serial driver

## Features

- SPI communication with MAX31723 temperature sensor
- 12-bit temperature measurement resolution
- Temperature data output via USB UART
- Automatic sensor configuration and initialization

## Code Functionality

The main application:
- Initializes the MAX31723 temperature sensor via SPI 
- Configures the sensor resolution to 12-bit
- Sets up USB UART communication
- Reads temperature data every 1,000,000 cycles
- Converts raw sensor data to temperature in degrees Celsius
- Outputs formatted temperature data to USB UART
- Provides status indicators for SPI communication

## Getting Started

### Setup

1. Connect the MAX31723 sensor to the Zalmotek RA8M1 Feather board
2. The chip select pin is configured on P4.15
3. Connect the board to your computer via USB
4. Open the project in Renesas e² studio
5. Build and flash the application to the board

### Configuration

The MAX31723 sensor is configured for 12-bit resolution:

```c
const uint8_t config_sensor[3] = {0x80, 0x06};
```

## Project Structure

- `src/hal_entry.c`: Main application entry point and control loop
- `src/spi_max31723.h`: MAX31723 sensor communication functions
- `src/usb_uart.h`: USB UART communication functions
- `src/common_utils.h`: Common utilities and definitions

## License

Proprietary

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 