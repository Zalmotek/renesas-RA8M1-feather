
# Changelog
This document keeps track of the changes that were made when porting the Arduino-Renesas Core to e2studio.

## Project structure
The original Arduino-Renesas Core project is composed of the following directories:

- [bootloaders](#bootloaders)
- [cores](#cores)
- [debugger](#debugger)
- [drivers](#drivers)
- [extras](#extras)
- [libraries](#libraries)
- [svd](#svd)
- [variants](#variants)

To keep projects clean these folders were added to a `core` directory. This way, inside the src folder of an e2studio project you should have the following directories:
- core
- libraries
    - Note that this is different from the libraries directory found inside the core folder
- SEGGER_RTT
    - Enables communication through the debugger using RTT
- common_utils.h 
    - Adds some good to have libraries and sets up an easier way to use the RTT interface
- hal_entry.cpp
    - Code written here does not execute
- handler_thread_entry.cpp
    - This thread sets up the board at boot time. It corresponds to the cores/arduino/main.cpp file
    - In the original Arduino-Renesas Core project the Interrupte Request Vector Table was stored at a specific address inside the stack. To maintain the dynamic nature of the FreeRTOS project and to avoid messing with the linker file this table is set somewhere in memory. 🔴***DANGER! This might lead to undefined behaviour.*** For now this seems to be the only way that allows the board to run.
- main_thread_entry.cpp
    - This thread is the "main function" of your program. Your code goes here

### bootloaders
This directory holds the bootloaders for the Renesas based boards in the form of hex files. 

 - v1.0 - removed

### cores
This directory holds the arduino folder in which many classic Arduino functionalities are being implmented. Inside the arduino folder there are the following directories and files:
- api 
    - v1.0 changes
        - Inside the deprecated-avr-comp/avr directory created dtostrf.c file based on the dtostrf.c.impl
        - Due to Windows being non-case sensitive String.h and String.cpp were renamed to String_.h and String_.cpp such that it won't be confused with the C++ string.h library. Consequently the include paths were slightly changed.
        - Inside the Common.h file commented the definition of the init function, the weak deifinition of the main function, and the setup and loop functions. 
- cm_backtrace
    - This directory contains the ARM Cortex-M series MCU error tracking library. For now this library is deemed unnecessary.
    - v1.0 - removed
- tinyusb
    - This directory contains files that redirect to the extras/tinyusb directory. For now this directory is deemed unnecessary.
    - v1.0 - removed
- usb
    - This directory contains the defintion of the Serial USB interface. This is heavily reliant on the Tiny USB project.
    - v1.0 changes
        - Modified the include paths to the Tiny USB files, making them relative
        - Due to the RA8M1 register structure the instruction BOOT_DOUBLE_TAP_DATA = DOUBLE_TAP_MAGIC; which saves some data to the backup registers needed to be rewritten in a more explicit manner.
- analog.cpp
    - v1.0 changes
        - Added a reference to IRQManager.h header file
        - Changed the ADC_Container constructor by modifying the extended config trigger and vref control
- Arduino.h
    - v1.0 changes
        - Added a reference to the common_utils.h header file
        - Added a defintion of the CPU clock frequency
        - Due to the RA8M1 register structure the instruction BOOT_DOUBLE_TAP_DATA = DOUBLE_TAP_MAGIC; which saves some data to the backup registers needed to be rewritten in a more explicit manner.
- boot.h
    - v1.0 changes
        - Commented the definitions of the BOOT_DOUBLE_TAP_DATA and DOUBLE_TAP_MAGIC as they are incompatible with the RA8M1 register structure
- cortex_handlers.c
    - Functionality used by cm_backtrace
    - v1.0 removed
- dac.cpp
    - v1.0 changes
        - In case the analogWrite value is too big it now fixes it to (1 << analogWriteResolution()) - 1 instead of (1 << analogWriteResolution). If the maximum value is set to (1 << analogWriteResolution()) it overflows and sets the pin to 0V.
- FspLinkIrq.h
    - v1.0 changes
        - Added an explicit relative path when including elc_defines.h header file
- FspTimer.h
    - v1.0 changes
        - Include the sync.h header file
        - Inside the AGTimer constructor set the cfg to the g_timer0_cfg and the ctrl to g_timer0_ctrl defined by the AGT stack. 🔴***Problematic if another AGT Stack is added.***
        - Inside the GPTimer constructor, depending on the cfg channel, set the cfg and ctrl to the coresponding g_timer_cfg and g_timer_ctrl defined by the GPT stack. Ignored the constructor extended config as it appears to break PWM functionality. 🔴***Problematic if another GPT Stack is added.***
        - Inside the set_duty_cycle function added the R_GPT_RESET command to force a reset of the timer
- FspTransfer.h
    - v1.0 removed
- Interrupts.cpp
    - v1.0 changes
        - Removed some redundant includes
- IRQManager.cpp
    - v1.0 changes 
        - Removed some redundant includes
        - Changed the sci_uart interrupts and variables to their sci_b_uart counterparts 
        - Changed the spi interrupts and variables to their spi_b counterparts
        - Commented the I2C slave and I2C SCI master code 
        - Commented the SCI SPI code 
- IRQManager.h
    - v1.0 changes
        - Made the includes more specific and relative
        - Commented the HAS_DMAC define
        - Changed the sci_uart interrupts and variables to their sci_b_uart counterparts 
        - Changed the spi interrupts and variables to their spi_b counterparts
        - Commented I2C slave and I2C SCI master code
        - Commented the SCI SPI code 
- main.cpp
    - v1.0 changes
        - The purpose of this file is to setup the board and so was moved to its own thread. The code can be found in the handler thread
- pinDefinitions.cpp
    - v1.0 changes
        - Removed some redundant includes
- Serial.cpp
    - v1.0 changes
        - Changed the FSP SCI UART functions to SCI B UART functions and the SCI UART configuration variables to SCI B UART configuration variables
        - Due to the register structure of the RA8M1 SSR_b->TEND was replaced with CSR_b->TEND
    - v1.1 changes
        - Inside the begin function added a check to determine the current channel and set the cfg and the ctrl defined by the UART stack. 
- Serial.h
    - v1.0 changes
        - Removed some redundant includes
        - Changed the SCI UART configuration variables to SCI B UART configuration variables
- time.cpp
    - v1.0 changes
        - Removed the static keyword from the timer_micros_callback function
        - Removed Azure RTOS checks
        - Changed R_AGT0->AGT to R_AGT0->AGT16.AGT
- vector_table.c
    - v1.0 changes
        - Changed some aspects of the old initialisation of the vector table and interrupt event_link_select. These are not used and should have no impact.
        - Explicitly set the g_interrupt_event_link_select vector to (bsp_interrupt_event_t)0
- WMath.cpp
    - v1.0 changes
        - Added a reference to the api/Common.h header file
        - Removed UNO R4 and Portenta specific implementation of true random number generators

### debugger
This directory holds some configuration files. It is unclear what they do.

- v1.0 - removed

### drivers
This directory holds driver files and executables. Not necessary for e2 studio implementation.

- v1.0 - removed

### extras
This directory holds extra resources needed at compile time like Tiny USB, e2studio projects, FSP, Filesystems, net, protobuf, UNO R4 WiFi bridge.

- v1.0 changes:
    - removed e2studio Projects
    - removed Filesystems
    - removed FSP
    - removed net
    - removed protobuf
    - removed tls
    - removed UNO R4 WiFi bridge
    - removed from Tiny USB every file and folder that is not used by the Serial USB. Changed some include paths to be able to link the project to the tusb_config.h header file.

### libraries
This directory holds Arduino libraries. These are implementations of commonly used functionalities.

- AnalogWave
    - Not investigated
    - v1.0 - removed
- Arduino_CAN
    - To be investigated / To be implemented
    - v1.0 - removed
- Arduino_FreeRTOS
    - Due to the fact that the project is already based on FreeRTOS this was not thorougly investigated
    - v1.0 - removed
- Arduino_LED_Matrix
    - UNO R4 only
    - v1.0 - removed
- BlockDevices
    - To be investigated / To be implemented
    - v1.0 - removed
- EEPROM
    - To be investigated / To be implemented
    - v1.0 - removed
- ESPhost
    - Portenta only
    - v1.0 - removed
- Ethernet
    - Portenta only
    - v1.0 - removed
- FATFilesystem
    - To be investigated / To be implemented
    - v1.0 - removed
- HID
    - Not investigated
    - v1.0 - removed
- I2S
    - To be investigated / To be implemented
    - v1.0 - removed
- LittleFilesystem
    - To be investigated / To be implemented
    - v1.0 - removed
- lwIpWrapper
    - Portenta only
    - v1.0 - removed
- OPAMP
    - Not Investigated
    - v1.0 - removed
- OTAUpdate
    - UNO R4 only
    - v1.0 - removed
- Preferences
    - Not investigated
    - v1.0 - removed
- RTC
    - Not investigated
    - v1.0 - removed
- SDU
    - UNO R4 only
    - v1.0 - removed
- SE05X
    - Portenta only
    - v1.0 - removed
- SFU
    - Portenta only
    - v1.0 - removed
- SoftwareATSE
    - UNO R4 only
    - v1.0 - removed
- SoftwareSerial
    - To be investigated / To be implemented
    - v1.0 - removed
- SPI
    - v1.0 changes
        - Changed include paths to relative include paths
        - Removed/commented the implementation of SCI SPI
        - Ported the SPI implementation to SPI_B
        - Added a 350 microsecond delay after writing data to the SDPR register before reading it to get the data from the SPI bus.
        - Changed the registers used for the transfer and configSPI function from the RA4M1 ones to the RA8M1 ones
- SSLClient
    - Portenta only
    - v1.0 - removed
- Storage
    - To be investigated / To be implemented
    - v1.0 - removed
- UsbHostMsd
    - Portenta only
    - v1.0 - removed
- UsbMsd
    - Portenta only
    - v1.0 - removed
- WDT
    - v1.0 changes
        - Removed the provided examples
        - Changed the default behaviour of the watchdog timer where it does not count if the debugger is connected by setting the value of the DBGSTOP_WDT register to 0
        - Set the _p_cfg to the g_wdt0_cfg and the _p_ctrl to g_wdt0_ctrl defined by the WDT stack. 🔴***Problematic if another WDT Stack is added.***
- WiFi
    - Portenta only
    - v1.0 - removed
- WifiS3
    - UNO R4 only
    - v1.0 - removed
- Wire
    - v1.0 changes
        - Removed/commented the implementation of SCI I2C and Slave I2c
        - Changed include paths to relative include paths
        - Removed FSP includes
        - Set the m_i2c_cfg to the g_i2c_master0_cfg and the m_i2c_ctrl to g_i2c_master0_ctrl defined by the I2C Master stack. 🔴***Problematic if another I2C Master Stack is added.***

### svd
This directory holds the svd files for the RA4M1 and the RA6M5. Not necessary for e2 studion implementaion.

- v1.0 - removed

### variants
This directory holds folders for every board and board specific information like ELC definitions, pin definitions, Tiny USB configuration. In the original Arduino-Renesas Core project this directory also includes C/C++ compile flags, linker files, FSP RA generated files and libraries.

- v1.0 changes
    - Removed every other board folder
    - Added the RA8M1_Feather directory
    - Set up the RA8M1 ELC defines
    - Set up the Tiny USB config files
    - Set up the pinmux.h and pins_arduino.h. If it is needed to add any other pin functionality the pinmux.h file should be updated accordingly
    - Finalised setting up the pins inside the variant.cpp file. Also modified the initVariant() function so that it sets up the timers for our PWM pins
- v1.1 changes
    - Changed the pins_arduino.h and the pinmux.h files to reflect the 2 new UART Serials

