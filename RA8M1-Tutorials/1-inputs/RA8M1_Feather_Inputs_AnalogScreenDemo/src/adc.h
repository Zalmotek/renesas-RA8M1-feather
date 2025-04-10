#ifndef ADC_h
#define ADC_h

#include "hal_data.h"
#include "common_utils.h"

#define ADC_12_BIT    (4096u)
#define ADC_16_BIT    (32768u)
#define V_ref         (3.3f)
#define ADC_H_LMT     (3103u)
#define ADC_L_LMT     (1241u)

/* Read the adc data available */
fsp_err_t adc_read_data(int ch, int *adc_raw, double *adc_volt);
/* close the open adc module  */
void deinit_adc_module(void);
/* Open the adc module, configures and initiates the scan*/
static fsp_err_t adc_scan_start(void);
/* stops the adc scan if the adc is continuous scan and then close the module */
static fsp_err_t adc_scan_stop(void);
/* Callback to handle window compare event */
void adc_callback(adc_callback_args_t * p_args);
int analogRead(int ch);
int analogRead(int ch, double *adc_volt);

/* Flag to notify that adc scan is started, so start reading adc */
volatile bool g_b_ready_to_read = false;
static uint16_t g_adc_data;
static bool g_window_comp_event = false;
extern const adc_cfg_t g_adc_cfg;

/*******************************************************************************************************************//**
 * @brief    This function open the ADC, configures and starts the scan
 * @param[IN]   None
 * @retval FSP_SUCCESS                  Upon successful open,configure adc,on success or calibrate and start adc scan
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful open or configure or start
 ***********************************************************************************************************************/
static fsp_err_t adc_scan_start(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status
    g_window_comp_event = false;
    if (false == g_b_ready_to_read) {
        /* Open/Initialize ADC module */
        err = R_ADC_Open (&g_adc_ctrl, &g_adc_cfg);
        /* handle error */
        if (FSP_SUCCESS != err) {
            /* ADC Failure message */
            //APP_ERR_PRINT("** R_ADC_C_Open API failed ** \r\n");
            return err;
        }
        /* Configures the ADC scan parameters */
        err = R_ADC_ScanCfg (&g_adc_ctrl, &g_adc_channel_cfg);
        /* handle error */
        if (FSP_SUCCESS != err) {
            /* ADC Failure message */
            //APP_ERR_PRINT("** R_ADC_C_ScanCfg API failed ** \r\n");
            return err;
        }
        /* Start the ADC scan*/
        err = R_ADC_ScanStart (&g_adc_ctrl);
        /* handle error */
        if (FSP_SUCCESS != err) {
            /* ADC Failure message */
            //APP_ERR_PRINT("** R_ADC_C_ScanStart API failed ** \r\n");
            return err;
        }
        /* Disable interrupts */
        R_BSP_IrqDisable((IRQn_Type)ADC_EVENT_SCAN_COMPLETE);
        /* Indication to start reading the adc data */
        g_b_ready_to_read = true;
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief    This function stops the scanning of adc
 * @param[IN]   None
 * @retval FSP_SUCCESS                  Upon successful stops the adc scan and closes the adc
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful stop or close of adc
 ***********************************************************************************************************************/
static fsp_err_t adc_scan_stop(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status
    /* Stop the scan if adc scan is started in continous scan mode else ignore */
    if((ADC_MODE_SINGLE_SCAN != g_adc_cfg.mode) && (true == g_b_ready_to_read )) {
        err = R_ADC_ScanStop (&g_adc_ctrl);
        /* handle error */
        if (FSP_SUCCESS != err) {
            /* ADC Failure message */
            //APP_ERR_PRINT("** R_ADC_C_ScanStop API failed ** \r\n");
            return err;
        }
        /* reset to indicate stop reading the adc data */
        g_b_ready_to_read = false;
        /* Close the ADC module*/
        err = R_ADC_Close (&g_adc_ctrl);
        /* handle error */
        if (FSP_SUCCESS != err) {
            /* ADC Failure message */
            //APP_ERR_PRINT("** R_ADC_C_Close API failed ** \r\n");
            return err;
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief    This function reads the adc output data from the prescribed channel and checks adc status
 * @param[IN]   None
 * @retval FSP_SUCCESS                  Upon successful stops the adc scan and closes the adc
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful stop or close of adc
 ***********************************************************************************************************************/
fsp_err_t adc_read_data(int ch, int *adc_raw, double *adc_volt) {
    fsp_err_t err = FSP_SUCCESS;     // Error status
    /* Read the result */
    if (ch == 0) {
        err = R_ADC_Read (&g_adc_ctrl, ADC_CHANNEL_0, &g_adc_data);
    }
    else {
        return FSP_ERR_NOT_INITIALIZED;
    }
    /* handle error */
    if (FSP_SUCCESS != err) {
        /* ADC Failure message */
        //APP_ERR_PRINT("** R_ADC_C_Read API failed ** \r\n");
        APP_PRINT("Problem at ch: "); APP_PRINT("%d",ch);
        return err;
    }
    *adc_raw = g_adc_data;
    *adc_volt = (float)((g_adc_data * V_ref)/ADC_12_BIT);

    /* In adc single scan mode after reading the data, it stops.So reset the g_b_ready_to_read state to
     * avoid reading unnecessarily. close the adc module as it gets opened in start scan command.*/
    if (ADC_MODE_SINGLE_SCAN == g_adc_cfg.mode || g_window_comp_event == true) {
        g_b_ready_to_read = false;
        /* Stop ADC scan */
        err = R_ADC_ScanStop (&g_adc_ctrl);
        /* Handle error */
        if (FSP_SUCCESS != err) {
            /* ADC ScanStop message */
            //APP_ERR_PRINT("** R_ADC_ScanStop API failed ** \r\n");
        }

        if(((g_window_comp_event == true)&&(ADC_MODE_SINGLE_SCAN == g_adc_cfg.mode))||(ADC_MODE_CONTINUOUS_SCAN == g_adc_cfg.mode)) {
            /* Print temperature status warning to RTT Viewer */
            if(ADC_L_LMT > g_adc_data) {
                //APP_PRINT("\r\nADC Voltage is below the Lower Limit. \r\n");
            }
            else if(ADC_H_LMT < g_adc_data) {
                //APP_PRINT("\r\nADC Voltage is above the Upper Limit.  \r\n");
            }
        }

        /* Close the ADC module*/
        err = R_ADC_Close (&g_adc_ctrl);
        /* handle error */
        if (FSP_SUCCESS != err) {
            /* ADC Failure message */
            //APP_ERR_PRINT("** R_ADC_C_Close API failed ** \r\n");
            return err;
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief    Close the adc driver and Handle the return closing API error, to the Application.
 * @param[IN]   None
 * @retval None.
 ***********************************************************************************************************************/
void deinit_adc_module(void) {
    fsp_err_t err = FSP_SUCCESS;
    /* close the ADC driver */
    err = R_ADC_Close (&g_adc_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err) {
        /* GPT Close failure message */
        //APP_ERR_PRINT("** R_ADC_Close API failed **  \r\n");
    }
}

/* Callback procedure for when window A compare event occurs */
void adc_callback(adc_callback_args_t * p_args) {
    if(ADC_EVENT_WINDOW_COMPARE_A == p_args->event) {
        g_window_comp_event = true;
        /* Disable ADC interrupt */
        IRQn_Type irq = R_FSP_CurrentIrqGet();
        R_BSP_IrqDisable(irq);
    }
}

int analogRead(int ch) {
    fsp_err_t err = FSP_SUCCESS;
    err = adc_scan_start();
    if (err != FSP_SUCCESS) {
        return -1;
    }
    int adc_raw;
    double adc_volt;
    err = adc_read_data(ch, &adc_raw, &adc_volt);
    if (err != FSP_SUCCESS) {
        return -1;
    }
    return adc_raw;
}

int analogRead(int ch, double *adc_volt) {
    fsp_err_t err = FSP_SUCCESS;
    *adc_volt = -1;
    err = adc_scan_start();
    if (err != FSP_SUCCESS) {
        return -1;
    }
    int adc_raw;
    err = adc_read_data(ch, &adc_raw, adc_volt);
    if (err != FSP_SUCCESS) {
        return -1;
    }
    return adc_raw;
}

#endif //ADC_h
