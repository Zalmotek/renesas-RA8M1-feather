extern "C" {
#ifndef _USB_UART_H_
#define _USB_UART_H_

#define LINE_CODING_LENGTH          (0x07U)
#define READ_BUF_SIZE               (8U)

#include "r_usb_pcdc_descriptor.h"
#include <stdio.h>
#include <string.h>
#include "common_init.h"
#include "common_utils.h"

/* Global variables */
extern const usb_descriptor_t usb_descriptor =
{
 g_apl_device,                   /* Pointer to the device descriptor */
 g_apl_configuration,            /* Pointer to the configuration descriptor for Full-speed */
 g_apl_hs_configuration,         /* Pointer to the configuration descriptor for Hi-speed */
 g_apl_qualifier_descriptor,     /* Pointer to the qualifier descriptor */
 g_apl_string_table,             /* Pointer to the string descriptor table */
 NUM_STRING_DESCRIPTOR
};

usb_status_t            usb_event;

const uint8_t *kitinfo = (uint8_t*) "Meow :3 \r\n";
const uint8_t *endline = (uint8_t*) "\r\n";
const uint8_t *comma = (uint8_t*) ",";
const uint8_t *minus = (uint8_t*) "-";
const uint8_t *point = (uint8_t*) ".";
const uint8_t *okstatus = (uint8_t*) "\033[0;42mOK\033[0m";
const uint8_t *nokstatus = (uint8_t*) "\033[0;41mNOK\033[0m";
const uint8_t *degreec = (uint8_t*) "°C";
const uint8_t *closingbracket = (uint8_t*)"]";
const uint8_t *openingbracket = (uint8_t*)"[";
const uint8_t *temperatureinfo = (uint8_t*) "temperature [";
const uint8_t *computationinfo = (uint8_t*) "Computation status [";
const uint8_t *spiinfo = (uint8_t*) "SPI status [";
const uint8_t *i2cinfo = (uint8_t*) "I2C status [";
const uint8_t *accelinfo = (uint8_t*) "acceleration(x, y, z) [";
const uint8_t *spacerinfo = (uint8_t*) ", ";
const uint8_t *digits[10] = {(uint8_t*) "0", (uint8_t*) "1", (uint8_t*) "2",
                              (uint8_t*) "3", (uint8_t*) "4", (uint8_t*) "5",
                              (uint8_t*) "6", (uint8_t*) "7", (uint8_t*) "8",
                              (uint8_t*) "9"};
bool  b_usb_attach = false;

/* Private functions */
static fsp_err_t check_for_write_complete(void);
static fsp_err_t print_to_console(char *p_data);

bool configured = false;

void usb_init();
void usb_init() {
    fsp_err_t err                           = FSP_SUCCESS;

    /* Open USB instance */
    err = R_USB_Open (&g_basic0_ctrl, &g_basic0_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
        APP_ERR_TRAP(err);
}

void handle_usb_event();
void handle_usb_event() {
    fsp_err_t err                           = FSP_SUCCESS;
    usb_event_info_t    event_info;
    uint8_t g_buf[READ_BUF_SIZE]            = {0};
    usb_pcdc_linecoding_t g_line_coding;

    /* Obtain USB related events */
    err = R_USB_EventGet (&event_info, &usb_event);

    /* Handle error */
    if (FSP_SUCCESS != err)
        APP_ERR_TRAP(err);

    /* USB event received by R_USB_EventGet */
    switch (usb_event)
    {
        case USB_STATUS_CONFIGURED:
        {
            err = R_USB_Read (&g_basic0_ctrl, g_buf, READ_BUF_SIZE, USB_CLASS_PCDC);
            /* Handle error */
            if (FSP_SUCCESS != err)
                APP_ERR_TRAP(err);

            configured = true;

            break;
        }

        case USB_STATUS_READ_COMPLETE:
        {
            if(b_usb_attach)
            {
                err = R_USB_Read (&g_basic0_ctrl, g_buf, READ_BUF_SIZE, USB_CLASS_PCDC);
            }
            /* Handle error */
            if (FSP_SUCCESS != err)
                APP_ERR_TRAP(err);

            break;
        }

        case USB_STATUS_REQUEST : /* Receive Class Request */
        {
            /* Check for the specific CDC class request IDs */
            if (USB_PCDC_SET_LINE_CODING == (event_info.setup.request_type & USB_BREQUEST))
            {
                err =  R_USB_PeriControlDataGet (&g_basic0_ctrl, (uint8_t *) &g_line_coding, LINE_CODING_LENGTH );
                /* Handle error */
                if (FSP_SUCCESS != err)
                    APP_ERR_TRAP(err);

            }
            else if (USB_PCDC_GET_LINE_CODING == (event_info.setup.request_type & USB_BREQUEST))
            {
                err =  R_USB_PeriControlDataSet (&g_basic0_ctrl, (uint8_t *) &g_line_coding, LINE_CODING_LENGTH );
                /* Handle error */
                if (FSP_SUCCESS != err)
                    APP_ERR_TRAP(err);
            }
            else if (USB_PCDC_SET_CONTROL_LINE_STATE == (event_info.setup.request_type & USB_BREQUEST))
            {
                err = R_USB_PeriControlStatusSet (&g_basic0_ctrl, USB_SETUP_STATUS_ACK);
                /* Handle error */
                if (FSP_SUCCESS != err)
                    APP_ERR_TRAP(err);
            }

            break;
        }

        case USB_STATUS_DETACH:
        case USB_STATUS_SUSPEND:
        {
            b_usb_attach = false;
            memset (g_buf, 0, sizeof(g_buf));
            break;
        }
        case USB_STATUS_RESUME:
        {
            b_usb_attach = true;
            break;
        }
        default:
        {
            break;
        }
    }
}

static void print_val(double n, bool floatingPoint = false, int decimals = 2);
static void print_val(double n, bool floatingPoint, int decimals) {
    if (n < 0) {
        print_to_console((char*)minus);
        n = -n;
    }

    int p = 1;
    int aux = (int)n;
    while (p <= aux) {
        p *= 10;
    }
    p /= 10;
    if (p == 0) {
        p = 1;
    }
    while (p) {
        print_to_console((char*)digits[((aux) / p) % 10]);
        p /= 10;
    }

    if (floatingPoint) {
        print_to_console((char*)point);
        p = 10;
        for (int i = 0; i < decimals; i++) {
            print_to_console((char*)digits[((int)(n * p)) % 10]);
            p *= 10;
        }
    }
}

static fsp_err_t print_to_console(char *p_data)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t len = ((uint32_t)strlen(p_data));

    err = R_USB_Write (&g_basic0_ctrl, (uint8_t*)p_data, len, USB_CLASS_PCDC);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    err = check_for_write_complete();
    if (FSP_SUCCESS != err)
    {
        /* Did not get the event hence returning error */
        return FSP_ERR_USB_FAILED;
    }
    return err;
}

static fsp_err_t check_for_write_complete(void)
{
    usb_status_t usb_write_event = USB_STATUS_NONE;
    int32_t timeout_count = UINT16_MAX;
    fsp_err_t err = FSP_SUCCESS;
    usb_event_info_t    event_info;

    do
    {
        err = R_USB_EventGet (&event_info, &usb_write_event);
        if (FSP_SUCCESS != err)
        {
            return err;
        }

        --timeout_count;

        if (0 > timeout_count)
        {
            timeout_count = 0;
            err = (fsp_err_t)USB_STATUS_NONE;
            break;
        }
    }while(USB_STATUS_WRITE_COMPLETE != usb_write_event);

    return err;
}

#endif //_USB_UART_H_
}
