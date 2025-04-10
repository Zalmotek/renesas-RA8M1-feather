# Intro
The purpose of this project is to enable compatibility between the hundreds of available Arduino libraries and our RA8M1 Feather board.

The project is built upon FreeRTOS because of seemingly incompatible features when using bare-metal (i.e. SCI UART is not working when the GPT Timer is enabled).

## Before anything else
Go to the following folder:

C:\Users\\%USERNAME%\\.eclipse\com.renesas.platform_{ID}\internal\projectgen\ra

Where {ID} is a user specific string of numbers. Copy and paste the modules and packs directories from this repo there. 

## Warning!
Modifying anything in the core directory, SEGGER_RTT directory, common_utils.h, hal_entry.cpp, handler_thread_entry.cpp, configuration.xml is 🔴***NOT RECOMMENDED***. Only do this if your application requires multiple threads.

Nicu is aware that there are errors inside the configuration.xml file. This is **by design**.

Do not terminate any RTOS thread. This will effectively kill the board. Make sure you always have an infinite while with a vTaskDelay() command in every thread.

Due to Windows being non-case sensitive String.h and String.cpp were renamed to String_.h and String_.cpp such that it won't be confused with the C++ string.h library. This may lead to some errors in poorly written Arduino libraries.

## Features
- Compatibility with any Arduino library*
- SPI
- I2C
- RX/TX UART
- Serial USB
- digital read and write on all digital pins
- analog read on all analog pins
- analog write on pin A0
- PWM on pins D6, D9, D10, D11, D12, D13
- Interrupts on pins D6, D9, D14
- Serial1(Rx/Tx), Serial2(D6/D9), Serial3(D11/D10)

(* terms and conditions may apply)

## Notes
To use the analog pins you must give a reference voltage to the VRF pin.

To use the Serial USB you must connect the USB pin to D5.

## Project structure
The original Arduino-Renesas Core project is composed of the following directories:

- [bootloaders](Changelog.md/#bootloaders)
- [cores](Changelog.md/#cores)
- [debugger](Changelog.md/#debugger)
- [drivers](Changelog.md/#drivers)
- [extras](Changelog.md/#extras)
- [libraries](Changelog.md/#libraries)
- [svd](Changelog.md/#svd)
- [variants](Changelog.md/#variants)

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

## How to add an Arduino library
Download the desired library and all its dependencies from github. Move the folders into the libraries directory (the one found **outside** of the cores folder). Go to Project -> C/C++ Project Settings, on the left go to C/C++ Build -> Settings and then to the Tool Settings tab. In the Tool Settings tab go to GNU Arm Cross C++ Compiler -> Includes and on the right to the right of Include paths (-l) hit Add... -> go to Workspace -> Your project directory -> src/libraries and select your library foders. Press Ok -> Ok -> Apply and Close.

## Current version: [1.1] - 22.10.2024