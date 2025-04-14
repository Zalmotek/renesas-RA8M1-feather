# Zalmotek RA8M1 Feather I2C Scanner

An I2C device scanner application for the Zalmotek RA8M1 Feather board powered by Renesas microcontroller.

## Overview

This project implements an I2C scanner that detects all connected I2C devices on the bus. The scanner reports the addresses of any found devices through the serial interface. Built for the Zalmotek RA8M1 Feather featuring Renesas RA8M1 microcontroller, it uses the built-in I2C (IIC) master peripheral.

## Hardware Requirements

- Zalmotek RA8M1 Feather board
- USB cable for power and communication
- I2C devices to scan (sensors, displays, etc.)

## Software Requirements

- Renesas e² studio or compatible IDE
- Renesas FSP (Flexible Software Package)
- Arduino core for Renesas RA
- Serial terminal application (115200 baud)

## Features

- Automatic scanning of all possible I2C addresses (1-127)
- Reports found devices and their addresses via serial output
- Continuous scanning with 5-second intervals
- Proper error handling for I2C communication

## Code Functionality

The main application:
- Initializes Serial communication at 115200 baud
- Sets up I2C (Wire) interface with default pins
- Continuously scans I2C address space (0x01-0x7F)
- Displays discovered I2C devices with their addresses in hexadecimal format
- Reports any communication errors encountered
- Provides a 5-second delay between scans

## Getting Started

### Setup

1. Connect your Zalmotek RA8M1 Feather board to your computer via USB
2. Connect I2C devices to the SDA and SCL pins of the RA8M1 Feather
3. Build and flash the application to your board
4. Open a serial terminal (115200 baud rate)
5. The application will start automatically and begin scanning for devices

### Configuration

By default, the scanner uses the primary I2C bus with the standard pins. To change the scan interval:

```cpp
// Change the delay between scans (in milliseconds)
delay(5000); // Currently set to 5 seconds
```

## Project Structure

- `src/main_thread_entry.cpp`: Main application code with I2C scanning logic
- `src/handler_thread_entry.cpp`: System initialization and runtime support
- `src/SEGGER_RTT/`: Debug output utilities
- `configuration.xml`: Project configuration for FSP

## License

This project is provided as an example application for the Zalmotek RA8M1 Feather board.

## Additional Resources

- [Zalmotek Website](https://zalmotek.com)
- [Zalmotek RA8M1 Website](https://zalmotek.com/products/RA8M1-Feather-SoM/)
- [SEGGER RTT Documentation](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) 