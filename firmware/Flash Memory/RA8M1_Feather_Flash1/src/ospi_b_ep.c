/***********************************************************************************************************************
 * File Name    : ospi_b_ep.c
 * Description  : Contains function definition.
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

#include "common_utils.h"
#include "ospi_b_commands.h"
#include "ospi_b_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup ospi_b_ep.c
 * @{
 **********************************************************************************************************************/

/* External variables */
extern spi_flash_direct_transfer_t g_ospi_b_direct_transfer [OSPI_B_TRANSFER_MAX];

/* Global variables */
uint8_t g_read_data [OSPI_B_APP_DATA_SIZE]  = {RESET_VALUE};
const uint8_t g_write_data [OSPI_B_APP_DATA_SIZE] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
};

/* function declarations*/
static fsp_err_t ospi_b_write_enable (void);
static fsp_err_t ospi_b_wait_operation (uint32_t timeout);
static fsp_err_t ospi_b_erase_operation (uint8_t * const p_address, uint32_t * const p_time);
static fsp_err_t ospi_b_write_operation (uint8_t * const p_address, uint32_t * const p_time);
static fsp_err_t ospi_b_read_operation (uint8_t * const p_address, uint32_t * const p_time);
static fsp_err_t timer_start_measure (void);
static fsp_err_t timer_get_measure (uint32_t * p_time);
static fsp_err_t ospi_b_setup_calibrate_data(void);

/*******************************************************************************************************************//**
 * @brief       This functions enables write and verify the read data.
 * @param       None
 * @retval      FSP_SUCCESS     Upon successful operation
 * @retval      FSP_ERR_ABORTED Upon incorrect read data.
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t ospi_b_write_enable (void)
{
    fsp_err_t                   err             = FSP_SUCCESS;
    spi_flash_direct_transfer_t transfer        = {RESET_VALUE};

    /* Transfer write enable command */
    transfer = g_ospi_b_direct_transfer[OSPI_B_TRANSFER_WRITE_ENABLE_SPI];
    err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED \r\n");

    /* Read Status Register */
    transfer = g_ospi_b_direct_transfer[OSPI_B_TRANSFER_READ_STATUS_SPI];
    err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
    APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED \r\n");

    /* Check Write Enable bit in Status Register */
    if(OSPI_B_WEN_BIT_MASK != (transfer.data & OSPI_B_WEN_BIT_MASK))
    {
        APP_ERR_RETURN(FSP_ERR_ABORTED, "Write enable FAILED\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function wait until OSPI operation completes.
 * @param[in]   timeout         Maximum waiting time
 * @retval      FSP_SUCCESS     Upon successful wait OSPI operating
 * @retval      FSP_ERR_TIMEOUT Upon time out
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation.
 **********************************************************************************************************************/
static fsp_err_t ospi_b_wait_operation (uint32_t timeout)
{
    fsp_err_t          err    = FSP_SUCCESS;
    spi_flash_status_t status = {RESET_VALUE};

    status.write_in_progress = true;
    while (status.write_in_progress)
    {
        /* Get device status */
        R_OSPI_B_StatusGet(&g_ospi_b_ctrl, &status);
        APP_ERR_RETURN(err, "R_OSPI_B_StatusGet API FAILED\r\n");
        if(RESET_VALUE == timeout)
        {
            APP_ERR_RETURN(FSP_ERR_TIMEOUT, "OSPI time out occurred\r\n");
        }
        R_BSP_SoftwareDelay(1, OSPI_B_TIME_UNIT);
        timeout --;
    }
    return err;
}

/**********************************************************************************************************************
 * @brief       This function performs an erase sector operation on the flash device.
 * @param[in]   *p_address  Pointer to flash device memory address
 * @param[out]  *p_time     Pointer will be used to store execute time
 * @retval      FSP_SUCCESS Upon successful erase operation
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t ospi_b_erase_operation (uint8_t * const p_address, uint32_t * const p_time)
{
    fsp_err_t err = FSP_SUCCESS;
    spi_flash_direct_transfer_t transfer = {RESET_VALUE};

    /* Enable write operations */
    err = ospi_b_write_enable();
    APP_ERR_RETURN(err, "ospi_b_write_enable FAILED\r\n");

    /* Start measure */
    err = timer_start_measure();
    APP_ERR_RETURN(err, "timer_start_measure FAILED\r\n");

    /* Erase sector */
    transfer.command = OSPI_B_COMMAND_SECTOR_ERASE_SPI;
    transfer.address = (uint32_t)p_address & ~((uint32_t)OSPI_B_SECTOR_SIZE - 1);  // Align to sector boundary
    transfer.command_length = OSPI_B_COMMAND_LENGTH_SPI;
    transfer.address_length = OSPI_B_ADDRESS_LENGTH_THREE;
    transfer.data_length = OSPI_B_DATA_LENGTH_ZERO;
    transfer.dummy_cycles = OSPI_B_DUMMY_CYCLE_WRITE_SPI;
    
    err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED\r\n");

    /* Wait until erase operation completes */
    err = ospi_b_wait_operation(OSPI_B_TIME_ERASE_4K);
    APP_ERR_RETURN(err, "ospi_b_wait_operation FAILED\r\n");

    /* Get execution time */
    err = timer_get_measure(p_time);
    APP_ERR_RETURN(err, "timer_get_measure FAILED\r\n");
    return err;
}

/**********************************************************************************************************************
 * @brief       This function performs an write operation on the flash device.
 * @param[in]   *p_address      Pointer to flash device memory address
 * @param[out]  *p_time     Pointer will be used to store execute time
 * @retval      FSP_SUCCESS Upon successful write operation
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t ospi_b_write_operation (uint8_t * const p_address, uint32_t * const p_time)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t erase_time = RESET_VALUE;
    spi_flash_direct_transfer_t transfer = {RESET_VALUE};

    APP_PRINT("\r\nStarting write operation...");
    APP_PRINT("\r\nTarget address: 0x%08x", (uint32_t)p_address);

    /* Erase sector before write data to flash device */
    APP_PRINT("\r\nErasing sector...");
    err = ospi_b_erase_operation(p_address, &erase_time);
    APP_ERR_RETURN(err, "ospi_b_erase_operation FAILED\r\n");
    APP_PRINT(" Done! (Took %lu us)", erase_time);

    /* Enable write operations */
    APP_PRINT("\r\nEnabling write...");
    err = ospi_b_write_enable();
    APP_ERR_RETURN(err, "ospi_b_write_enable FAILED\r\n");
    APP_PRINT(" Done!");

    /* Start measure */
    err = timer_start_measure();
    APP_ERR_RETURN(err, "timer_start_measure FAILED\r\n");

    /* Make sure we don't cross page boundary */
    uint32_t page_offset = (uint32_t)p_address & (OSPI_B_PAGE_SIZE - 1);
    uint32_t write_size = MIN(OSPI_B_PAGE_SIZE - page_offset, OSPI_B_APP_DATA_SIZE);
    
    APP_PRINT("\r\nWriting %lu bytes...", write_size);
    /* Write data byte by byte */
    for(uint32_t i = 0; i < write_size; i++) {
        /* Enable write for each byte */
        err = ospi_b_write_enable();
        APP_ERR_RETURN(err, "ospi_b_write_enable FAILED\r\n");

        /* Setup page program command */
        transfer.command = OSPI_B_COMMAND_PAGE_PROGRAM_SPI;
        transfer.address = (uint32_t)p_address + i;
        transfer.command_length = OSPI_B_COMMAND_LENGTH_SPI;
        transfer.address_length = OSPI_B_ADDRESS_LENGTH_THREE;
        transfer.data_length = OSPI_B_DATA_LENGTH_ONE;
        transfer.dummy_cycles = OSPI_B_DUMMY_CYCLE_WRITE_SPI;
        transfer.data = g_write_data[i];

        err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
        APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED\r\n");

        /* Wait for this byte write to complete */
        err = ospi_b_wait_operation(OSPI_B_TIME_WRITE);
        APP_ERR_RETURN(err, "ospi_b_wait_operation FAILED\r\n");

        /* Verify the byte was written correctly */
        transfer.command = OSPI_B_COMMAND_READ_DATA_SPI;
        err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
        APP_ERR_RETURN(err, "Read verification failed\r\n");
        
        if((uint8_t)transfer.data != g_write_data[i]) {
            APP_PRINT("\r\nImmediate verify failed at offset %lu: Expected 0x%02X, Got 0x%02X",
                i, g_write_data[i], (uint8_t)transfer.data);
        }

        APP_PRINT(".");
    }
    APP_PRINT(" Done!");

    /* Get execution time */
    err = timer_get_measure(p_time);
    APP_ERR_RETURN(err, "timer_get_measure FAILED\r\n");

    /* Final verification */
    uint8_t verify_buffer[OSPI_B_APP_DATA_SIZE];
    APP_PRINT("\r\nVerifying written data...");
    
    /* Read back data byte by byte */
    transfer.command = OSPI_B_COMMAND_READ_DATA_SPI;
    transfer.dummy_cycles = 0;  // No dummy cycles needed for basic read
    for(uint32_t i = 0; i < write_size; i++) {
        transfer.address = (uint32_t)p_address + i;
        err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
        APP_ERR_RETURN(err, "Read verification failed\r\n");
        verify_buffer[i] = (uint8_t)transfer.data;
        APP_PRINT(".");
    }
    APP_PRINT(" Done!");

    if (memcmp(g_write_data, verify_buffer, write_size) == 0) {
        APP_PRINT("\r\nWrite verification successful!");
    } else {
        APP_PRINT("\r\nWrite verification failed!");
    }
    APP_PRINT("\r\nWrite operation completed in %lu us\r\n", *p_time);

    return err;
}

/**********************************************************************************************************************
 * @brief       This function performs an read operation on the flash device.
 * @param[in]   *p_address  Pointer to flash device memory address
 * @param[out]  *p_time     Pointer will be used to store execute time
 * @retval      FSP_SUCCESS Upon successful read operation
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t ospi_b_read_operation (uint8_t * const p_address, uint32_t * const p_time)
{
    fsp_err_t err = FSP_SUCCESS;
    spi_flash_direct_transfer_t transfer = {RESET_VALUE};

    /* Clean read buffer */
    memset(&g_read_data, RESET_VALUE, OSPI_B_APP_DATA_SIZE);

    /* Start measure */
    err = timer_start_measure();
    APP_ERR_RETURN(err, "timer_start_measure FAILED\r\n");

    /* Read data byte by byte */
    transfer.command = OSPI_B_COMMAND_READ_DATA_SPI;
    transfer.command_length = OSPI_B_COMMAND_LENGTH_SPI;
    transfer.address_length = OSPI_B_ADDRESS_LENGTH_THREE;
    transfer.data_length = OSPI_B_DATA_LENGTH_ONE;
    transfer.dummy_cycles = 0;  // No dummy cycles needed for basic read

    APP_PRINT("\r\nReading data...");
    for(uint32_t i = 0; i < OSPI_B_APP_DATA_SIZE; i++) {
        transfer.address = (uint32_t)p_address + i;
        err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
        APP_ERR_RETURN(err, "Read operation failed\r\n");
        g_read_data[i] = (uint8_t)transfer.data;
        APP_PRINT(".");
    }
    APP_PRINT(" Done!");

    /* Verify read data matches written data */
    if (memcmp(g_write_data, g_read_data, OSPI_B_APP_DATA_SIZE) != 0) {
        APP_PRINT("\r\nRead data verification failed!");
        APP_PRINT("\r\nRead operation failed - returning to menu\r\n");
        /* Get execution time before returning */
        timer_get_measure(p_time);
        return FSP_ERR_ABORTED;  // Special case for verification failure
    } else {
        APP_PRINT("\r\nRead data verification successful!");
    }

    /* Get execution time */
    err = timer_get_measure(p_time);
    APP_ERR_RETURN(err, "timer_get_measure FAILED\r\n");
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This functions initializes OSPI module and Flash device.
 * @param       None
 * @retval      FSP_SUCCESS     Upon successful initialization of OSPI module and Flash device
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t ospi_b_init (void)
{
    fsp_err_t                   err             = FSP_SUCCESS;
    spi_flash_direct_transfer_t transfer        = {RESET_VALUE};

    /* Open OSPI module */
    err = R_OSPI_B_Open(&g_ospi_b_ctrl, &g_ospi_b_cfg);
    APP_ERR_RETURN(err, "R_OSPI_B_Open API FAILED \r\n");

    /* Switch OSPI module to 1S-1S-1S mode to configure flash device */
    err = R_OSPI_B_SpiProtocolSet(&g_ospi_b_ctrl, SPI_FLASH_PROTOCOL_EXTENDED_SPI);
    APP_ERR_RETURN(err, "R_OSPI_B_SpiProtocolSet API FAILED \r\n");

    /* Reset flash device by driving OM_RESET pin */
    R_XSPI->LIOCTL_b.RSTCS0 = 0;
    R_BSP_SoftwareDelay(OSPI_B_TIME_RESET_PULSE, OSPI_B_TIME_UNIT);
    R_XSPI->LIOCTL_b.RSTCS0 = 1;
    R_BSP_SoftwareDelay(OSPI_B_TIME_RESET_SETUP, OSPI_B_TIME_UNIT);

    /* Transfer write enable command */
    err = ospi_b_write_enable();
    APP_ERR_RETURN(err, "ospi_b_write_enable FAILED \r\n");

    /* Read and verify Status Register */
    transfer = g_ospi_b_direct_transfer[OSPI_B_TRANSFER_READ_STATUS_SPI];
    err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
    APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED \r\n");
    if(transfer.data & OSPI_B_BUSY_BIT_MASK)
    {
        APP_ERR_RETURN(FSP_ERR_ABORTED, "Device is busy\r\n");
    }

    /* Read and verify Configuration Register */
    transfer = g_ospi_b_direct_transfer[OSPI_B_TRANSFER_READ_DEVICE_ID_SPI];
    err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
    APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED \r\n");

    /* Setup calibrate data */
    err = ospi_b_setup_calibrate_data();
    APP_ERR_RETURN(err, "ospi_b_setup_calibrate_data FAILED \r\n");

    return err;
}

/**********************************************************************************************************************
 * @brief       This function reads flash device id
 * @param[out]  *p_device_id        Pointer will be used to store device id
 * @retval      FSP_SUCCESS         Upon successful direct transfer operation
 * @retval      FSP_ERR_ABORTED     On incorrect device id read.
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful operation
 **********************************************************************************************************************/
fsp_err_t ospi_b_read_device_id (uint32_t * const p_id)
{
    fsp_err_t                   err             = FSP_SUCCESS;
    spi_flash_direct_transfer_t transfer        = {RESET_VALUE};

    /* Read and check flash device ID */
    transfer = g_ospi_b_direct_transfer[OSPI_B_TRANSFER_READ_DEVICE_ID_SPI];
    err = R_OSPI_B_DirectTransfer(&g_ospi_b_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
    APP_ERR_RETURN(err, "R_OSPI_B_DirectTransfer API FAILED \r\n");

    /* Check each byte of the JEDEC ID */
    uint8_t manufacturer_id = (uint8_t)(transfer.data & 0xFF);
    uint8_t memory_type = (uint8_t)((transfer.data >> 8) & 0xFF);
    uint8_t memory_density = (uint8_t)((transfer.data >> 16) & 0xFF);

    if((OSPI_B_MANUFACTURER_ID != manufacturer_id) || 
       (OSPI_B_DEVICE_ID_TYPE != memory_type) ||
       (OSPI_B_DEVICE_ID_DENSITY != memory_density))
    {
        APP_ERR_PRINT("\r\nExpected ID: 0x%02X%02X%02X, Received ID: 0x%02X%02X%02X\r\n",
            OSPI_B_MANUFACTURER_ID, OSPI_B_DEVICE_ID_TYPE, OSPI_B_DEVICE_ID_DENSITY,
            manufacturer_id, memory_type, memory_density);
        APP_ERR_RETURN(FSP_ERR_ABORTED, "JEDEC ID verification failed\r\n");
    }

    /* Get flash device ID */
    *p_id = transfer.data;
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function performs OSPI operations according to the selections made by the user.
 * @param[in]   *p_address      Pointer to flash device memory
 * @retval      FSP_SUCCESS     Upon successful OSPI operation
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
fsp_err_t ospi_b_operation (uint8_t * p_address)
{
    fsp_err_t       err                         = FSP_SUCCESS;
    uint32_t        execute_time                = RESET_VALUE;
    uint8_t         rtt_read [BUFFER_SIZE_DOWN] = {RESET_VALUE};
    const uint8_t   spi_mode_string []          = "1S-1S-1S Protocol Mode";
    const uint8_t   opi_mode_string []          = "8D-8D-8D Protocol Mode";
    uint8_t const   * p_mode_string             = NULL;

    /* Get OSPI mode name of current OSPI instance */
    p_mode_string = (SPI_FLASH_PROTOCOL_EXTENDED_SPI == g_ospi_b_ctrl.spi_protocol)
            ? spi_mode_string : opi_mode_string;

    /* Print Sub Menu option */
    APP_PRINT(SUB_MENU, p_mode_string);

    /* Loop */
    while(true)
    {
        if(APP_CHECK_DATA)
        {
            /* Clean RTT Viewer input buffer */
            memset(rtt_read, RTT_NULL_CHAR, BUFFER_SIZE_DOWN);

            /* Get RTT Viewer input buffer */
            APP_READ(rtt_read);

            /* Handle RTT input */
            switch(rtt_read[RTT_CHECK_INDEX])
            {
                case RTT_SELECT_WRITE_OPERATION_CHAR:
                {
                    err = ospi_b_write_operation(p_address, &execute_time);
                    if (err != FSP_SUCCESS) {
                        APP_PRINT("\r\nWrite operation failed - returning to menu\r\n");
                        continue;  // Return to menu
                    }
                    APP_PRINT("\r\n%s : Write %d bytes completed successfully in %d nanoseconds\r\n",
                             p_mode_string, OSPI_B_APP_DATA_SIZE, execute_time);
                    break;
                }

                case RTT_SELECT_READ_OPERATION_CHAR:
                {
                    err = ospi_b_read_operation(p_address, &execute_time);
                    if (err == FSP_ERR_ABORTED) {
                        continue;  // Return to menu on verification failure
                    }
                    else if (err != FSP_SUCCESS) {
                        APP_ERR_RETURN(err, "ospi_b_read_operation FAILED\r\n");
                    }
                    APP_PRINT("\r\n%s : Read %d bytes completed successfully in %d nanoseconds\r\n",
                             p_mode_string, OSPI_B_APP_DATA_SIZE, execute_time);
                    break;
                }

                case RTT_SELECT_ERASE_OPERATION_CHAR:
                    /* Performs OSPI erase operation */
                    err = ospi_b_erase_operation(p_address, &execute_time);
                    APP_ERR_RETURN(err, "ospi_b_erase_operation FAILED\r\n");

                    /* Print execution time */
                    APP_PRINT("%s : Erase sector completed successfully in %d nanoseconds\r\n",
                              p_mode_string, execute_time);
                    break;

                case RTT_EXIT_SUB_MENU_CHAR:
                    APP_PRINT ("\r\nGo back to Main Menu\r\n");
                    return err;

                default:
                    APP_PRINT ("\r\nInvalid input. Provide a valid input\r\n");
                    break;
            }

            /* Print Sub Menu option */
            APP_PRINT(SUB_MENU, p_mode_string);
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function starts GPT module to measure execution time of an OSPI operation.
 * @param       None
 * @retval      FSP_SUCCESS Upon successful operation
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t timer_start_measure (void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Clear timer counter */
    err = R_GPT_Reset (&g_timer_ctrl);
    APP_ERR_RETURN(err, "R_GPT_Reset FAILED\r\n");

    /* Start timer */
    err = R_GPT_Start (&g_timer_ctrl);
    APP_ERR_RETURN(err, "R_GPT_Start FAILED\r\n");
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This Function measures the timing info by reading the timer.
 * @param[in]   *p_time     Pointer will be used to store the OSPI operation execution time
 * @retval      FSP_SUCCESS Upon successful operation
 * @retval      Any Other Error code apart from FSP_SUCCESS Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t timer_get_measure (uint32_t * p_time)
{
    fsp_err_t       err             = FSP_SUCCESS;
    timer_status_t  timer_status    = {RESET_VALUE};
    timer_info_t    timer_info      = {RESET_VALUE};

    /* Get status of timer */
    err = R_GPT_StatusGet (&g_timer_ctrl, &timer_status);
    APP_ERR_RETURN(err, "R_GPT_StatusGet FAILED\r\n");

    /* Get info of timer */
    err = R_GPT_InfoGet (&g_timer_ctrl, &timer_info);
    APP_ERR_RETURN(err, "R_GPT_InfoGet FAILED\r\n");

    /* Stop timer */
    err = R_GPT_Stop(&g_timer_ctrl);
    APP_ERR_RETURN(err, "R_GPT_Stop FAILED\r\n");

    /* Convert count value to nanoseconds unit */
    *p_time = (timer_status.counter * 100) / (timer_info.clock_frequency / 10000000);
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This functions initializes GPT module used to measure OSPI operation execution time.
 * @param       None
 * @retval      FSP_SUCCESS Upon successful operation
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful operation
 **********************************************************************************************************************/
fsp_err_t timer_init (void)
{
    fsp_err_t err = FSP_SUCCESS;

    err = R_GPT_Open(&g_timer_ctrl, &g_timer_cfg);
    APP_ERR_RETURN(err, "R_GPT_Open FAILED\r\n");
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function sets up the auto-calibrate data for the flash.
 * @param       None
 * @retval      FSP_SUCCESS Upon successful operation
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful operation
 **********************************************************************************************************************/
static fsp_err_t ospi_b_setup_calibrate_data(void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t g_autocalibration_data[] =
    {
        0xFFFF0000U,
        0x000800FFU,
        0x00FFF700U,
        0xF700F708U
    };

    /* Verify auto-calibration data */
    if (RESET_VALUE != memcmp((uint8_t *)OSPI_B_APP_ADDRESS(OSPI_B_SECTOR_THREE),
            &g_autocalibration_data, sizeof(g_autocalibration_data)))
    {
        /* Erase the flash sector that stores auto-calibration data */
        err = R_OSPI_B_Erase (&g_ospi_b_ctrl,
                              (uint8_t *)OSPI_B_APP_ADDRESS(OSPI_B_SECTOR_THREE), OSPI_B_SECTOR_SIZE_4K);
        APP_ERR_RETURN(err, "R_OSPI_B_Erase API FAILED \r\n");

        /* Wait until erase operation completes */
        err = ospi_b_wait_operation(OSPI_B_TIME_ERASE_4K);
        APP_ERR_RETURN(err, "ospi_b_wait_operation FAILED\r\n");

        /* Write auto-calibration data to the flash */
        err = R_OSPI_B_Write(&g_ospi_b_ctrl, (uint8_t *)&g_autocalibration_data,
                             (uint8_t *)OSPI_B_APP_ADDRESS(OSPI_B_SECTOR_THREE), sizeof(g_autocalibration_data));
        APP_ERR_RETURN(err, "R_OSPI_B_Write API FAILED \r\n");

        /* Wait until write operation completes */
        err = ospi_b_wait_operation(OSPI_B_TIME_WRITE);
        APP_ERR_RETURN(err, "ospi_b_wait_operation FAILED\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ospi_b_ep.c)
 **********************************************************************************************************************/
