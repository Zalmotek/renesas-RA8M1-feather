#ifndef _WIRE_H_
#define _WIRE_H_

#define I2C_BUFF_TX_SIZE		8000  /*I2C Transmission Buffer Size*/
#define I2C_BUFF_RX_SIZE		(0x50)  /*I2C Reception Buffer Size*/

#include "i2c_op.h"

static bool init = false;

static uint8_t i2c_buff_tx[I2C_BUFF_TX_SIZE] = {0};
static uint8_t i2c_buff_rx[I2C_BUFF_RX_SIZE] = {0};

static int tx_idx, rx_idx, rx_start;

static fsp_err_t wire_clear_buffer_n(uint8_t *buff, uint32_t len) {
	if (buff == NULL) {
		return FSP_ERR_INVALID_POINTER;
	}

	for (size_t i = 0; i < len; i++) {
		buff[i] = 0;
	}
	return FSP_SUCCESS;
}

static fsp_err_t wire_init_communication(uint8_t address) {
    fsp_err_t err = FSP_SUCCESS;

    err = I2CStart();

    if(err == FSP_SUCCESS) {
        err = R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, address, I2C_MASTER_ADDR_MODE_7BIT);
        if (FSP_SUCCESS != err) {
        	APP_ERR_PRINT("** I2C Slave Address Set Failed ** \r\n");
        	return err;
        }
    }
    else {
    	return err;
    }

    /*Clear transmission and reception buffer*/
    tx_idx = rx_idx = 0;
    wire_clear_buffer_n(i2c_buff_tx, I2C_BUFF_TX_SIZE);
    wire_clear_buffer_n(i2c_buff_rx, I2C_BUFF_RX_SIZE);

    return err;
}

static fsp_err_t wire_write(uint8_t* buff, uint32_t len, bool restart) {
    fsp_err_t err = I2CWrite(buff, len, restart);
    if (err == FSP_SUCCESS) {
    	err = wire_clear_buffer_n(buff, len);
    	tx_idx = 0;
    }
    return err;
}

static fsp_err_t wire_read(uint8_t* buff, uint32_t len, bool restart) {
	rx_start = 0;
	fsp_err_t err = wire_clear_buffer_n(buff, rx_idx);
	rx_idx = 0;
	if (err == FSP_SUCCESS) {
		err = I2CRead(buff, len, restart);
		if (err != FSP_SUCCESS) {
			APP_ERR_PRINT("** wire_read failed ** \r\n");
			return err;
		}
		rx_idx = len;
	}
	else {
	    APP_ERR_PRINT("** wire_clear_buffer_n failed ** \r\n");
	}
    return err;
}

static fsp_err_t requestFrom(uint8_t devAddr, uint32_t count) {
	(void)devAddr;

	fsp_err_t err = wire_read(i2c_buff_rx, count, false);
	if (err != FSP_SUCCESS) {
		APP_ERR_PRINT("** requestFrom failed ** \r\n");
	}
    return err;
}

static fsp_err_t beginTransmission(uint8_t address) {
	fsp_err_t err = FSP_SUCCESS;
	if (init == false) {
		err = wire_init_communication(address);
		init = true;
	}
	if (err != FSP_SUCCESS) {
		APP_ERR_PRINT("** beginTransmission failed ** \r\n");
		return err;
	}
	return err;
}

static fsp_err_t write(uint8_t data) {
	if (tx_idx < I2C_BUFF_TX_SIZE) {
		i2c_buff_tx[tx_idx++] = data;
		return FSP_SUCCESS;
	}
	else {
		APP_ERR_PRINT("** write failed ** \r\n");
		return FSP_ERR_OUT_OF_MEMORY;
	}
}

static void endTransmission(bool restart) {
	wire_write(i2c_buff_tx, tx_idx, restart);
	wire_clear_buffer_n(i2c_buff_tx, tx_idx);
	tx_idx = 0;
}


static fsp_err_t wire_read_register(uint8_t reg_addr, uint8_t* buff, uint32_t len = 1) {
    fsp_err_t err = write(reg_addr);
    endTransmission(true);
    if(err == FSP_SUCCESS) {
        err = wire_read(buff, len, false);
    }
    else {
        APP_ERR_PRINT("** wire_read_register failed ** \r\n");
    }
    return err;
}


static uint8_t read() {
	return i2c_buff_rx[rx_start++];
}

static bool available() {
	return rx_start != rx_idx;
}

#endif
