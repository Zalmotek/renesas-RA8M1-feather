/***********************************************************************************************************************
 * File Name    : ospi_b_commands.h
 * Description  : Contains data structures and functions used in ospi_commands.h
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#ifndef OSPI_B_COMMANDS_H_
#define OSPI_B_COMMANDS_H_

#include "hal_data.h"

/* Utility macros */
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/* Macro for OSPI command code */
#define OSPI_B_COMMAND_WRITE_ENABLE_SPI             (0x06)    // Write Enable
#define OSPI_B_COMMAND_PAGE_PROGRAM_SPI             (0x02)    // Page Program
#define OSPI_B_COMMAND_READ_STATUS_SPI              (0x05)    // Read Status Register
#define OSPI_B_COMMAND_SECTOR_ERASE_SPI            (0x20)    // Sector Erase (4KB)
#define OSPI_B_COMMAND_READ_DEVICE_ID_SPI           (0x9F)    // Read ID
#define OSPI_B_COMMAND_READ_DATA_SPI               (0x03)    // Read Data
#define OSPI_B_COMMAND_READ_FLAG_STATUS_SPI        (0x70)    // Read Flag Status Register

/* Macro for OSPI command length */
#define OSPI_B_COMMAND_LENGTH_SPI                   (1U)

/* Macro for OSPI transfer address */
#define OSPI_B_ADDRESS_DUMMY                        (0U)
#define OSPI_B_ADDRESS_LENGTH_ZERO                  (0U)
#define OSPI_B_ADDRESS_LENGTH_THREE                 (3U)
#define OSPI_B_ADDRESS_LENGTH_FOUR                  (4U)

/* Macro for OSPI transfer data */
#define OSPI_B_DATA_DUMMY                           (0U)
#define OSPI_B_DATA_LENGTH_ZERO                     (0U)
#define OSPI_B_DATA_LENGTH_ONE                      (1U)
#define OSPI_B_DATA_LENGTH_TWO                      (2U)
#define OSPI_B_DATA_LENGTH_FOUR                     (4U)

/* Macro for OSPI transfer dummy cycles */
#define OSPI_B_DUMMY_CYCLE_WRITE_SPI                (0U)
#define OSPI_B_DUMMY_CYCLE_READ_STATUS_SPI          (0U)
#define OSPI_B_DUMMY_CYCLE_READ_REGISTER_SPI        (0U)
#define OSPI_B_DUMMY_CYCLE_READ_MEMORY_SPI          (8U)      // 8 dummy cycles for fast read

/* Macro for flash device register address */
#define OSPI_B_ADDRESS_STR1V_REGISTER               (0x00800000)
#define OSPI_B_ADDRESS_STR2V_REGISTER               (0x00800001)
#define OSPI_B_ADDRESS_CFR1V_REGISTER               (0x00800002)
#define OSPI_B_ADDRESS_CFR2V_REGISTER               (0x00800003)
#define OSPI_B_ADDRESS_CFR3V_REGISTER               (0x00800004)
#define OSPI_B_ADDRESS_CFR4V_REGISTER               (0x00800005)
#define OSPI_B_ADDRESS_CFR5V_REGISTER               (0x00800006)

/* Macros for configure flash device */
/* Configuration Register 2 (CR2V) bits:
 * Bit 7: Reserved (0)
 * Bit 6: Reserved (0)
 * Bit 5-4: Address Bytes = 11 (4-byte address mode)
 * Bit 3-0: Dummy Clock Cycles = 8 (for Fast Read operations)
 */
#define OSPI_B_DATA_CFR2V_REGISTER                  (0x38)    // 0b00111000

/* Configuration Register 3 (CR3V) bits:
 * Bit 7: Reserved (0)
 * Bit 6: WPS (Write Protect Selection) = 0
 * Bit 5: Reserved (0)
 * Bit 4: Reserved (0)
 * Bit 3-0: Wait States for Read Register = 8
 */
#define OSPI_B_DATA_CFR3V_REGISTER                  (0x08)    // 0b00001000

/* Configuration Register 5 (CR5V) bits:
 * Bit 7: Reserved (0)
 * Bit 6: Reserved (0)
 * Bit 5: Reserved (0)
 * Bit 4: Reserved (0)
 * Bit 3: Reserved (0)
 * Bit 2: IBL (Input Buffer Latch)= 0
 * Bit 1: DQS (Data Strobe) = 0
 * Bit 0: Hold/Reset = 0
 */
#define OSPI_B_DATA_SET_SPI_CFR5V_REGISTER        (0x00)    // 0b00000000

/* Flash device timing */
#define OSPI_B_PAGE_SIZE                           (256)     // Page size for write operations
#define OSPI_B_SECTOR_SIZE                         (4096)    // Sector size for erase operations

/* Macro for flash device */
#define OSPI_B_MANUFACTURER_ID              (0x20)          // Micron
#define OSPI_B_DEVICE_ID_TYPE              (0xBA)          // MT25QL series
#define OSPI_B_DEVICE_ID_DENSITY           (0x18)          // 128Mb

/* Flash device status bit masks */
#define OSPI_B_WEN_BIT_MASK                        (0x02)    // Write Enable Latch bit
#define OSPI_B_BUSY_BIT_MASK                       (0x01)    // Write In Progress bit

/* Update the transfer structure for JEDEC ID read */
typedef enum e_ospi_b_transfer
{
     OSPI_B_TRANSFER_WRITE_ENABLE_SPI = 0,
         OSPI_B_TRANSFER_WRITE_CFR2V_SPI,
         OSPI_B_TRANSFER_WRITE_CFR3V_SPI,
         OSPI_B_TRANSFER_WRITE_CFR5V_SPI,
         OSPI_B_TRANSFER_READ_STATUS_SPI,
         OSPI_B_TRANSFER_READ_CFR2V_SPI,
         OSPI_B_TRANSFER_READ_CFR3V_SPI,
         OSPI_B_TRANSFER_READ_CFR5V_SPI,
         OSPI_B_TRANSFER_READ_DEVICE_ID_SPI,

         OSPI_B_TRANSFER_MAX
} ospi_b_transfer_t;

#endif /* OSPI_B_COMMANDS_H_ */
