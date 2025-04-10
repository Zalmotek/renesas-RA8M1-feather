#ifndef _I2COP_H_
#define _I2COP_H_

#include "common_utils.h"
#include "hal_data.h"

static volatile i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
    }
}

static fsp_err_t validate_i2c_event(void)
{
    uint16_t local_time_out = UINT16_MAX;

    /* resetting call back event capture variable */
    i2c_event = (i2c_master_event_t)RESET_VALUE;

    do
    {
        /* This is to avoid infinite loop */
        --local_time_out;

        if(RESET_VALUE == local_time_out)
        {
            return FSP_ERR_TRANSFER_ABORTED;
        }

    }while(i2c_event == RESET_VALUE);

    if(i2c_event != I2C_MASTER_EVENT_ABORTED)
    {
        i2c_event = (i2c_master_event_t)RESET_VALUE;  // Make sure this is always Reset before return
        return FSP_SUCCESS;
    }

    i2c_event = (i2c_master_event_t)RESET_VALUE; // Make sure this is always Reset before return
    return FSP_ERR_TRANSFER_ABORTED;
    //return FSP_SUCCESS;
}

static fsp_err_t I2CStart() {
    //R_IIC_MASTER_Close(&g_i2c_master0_ctrl);
    fsp_err_t err = R_IIC_MASTER_Open(&g_i2c_master0_ctrl, &g_i2c_master0_cfg);
    if (FSP_SUCCESS != err) {
        APP_ERR_PRINT("** R_IIC_MASTER_Open API failed ** \r\n");
    }
    return err;
}

static fsp_err_t I2CRead(uint8_t *buff, uint32_t buff_len, uint8_t restart) {
    fsp_err_t err = R_IIC_MASTER_Read(&g_i2c_master0_ctrl, buff, buff_len, restart);
    validate_i2c_event();
    if (FSP_SUCCESS != err) {
        APP_ERR_PRINT("** I2C Read Failed ** \r\n");
    }
    return err;
}

static fsp_err_t I2CWrite(uint8_t *buff, uint32_t buff_len, uint8_t restart) {
    fsp_err_t err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, buff, buff_len, restart);
    validate_i2c_event();
    if (err != FSP_SUCCESS) {
        APP_ERR_PRINT("** I2C Write Failed ** \r\n");
    }
    return err;
}

#endif //_I2COP_H_
