#include "usb_uart.h"
#include "AMS_OSRAM_AS7343.h"

#define DESIRED_FREQ 50 // Desired output frequency measured in Hz

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

void delay(uint32_t dt);
void delay(uint32_t dt) {
    R_BSP_SoftwareDelay(dt, BSP_DELAY_UNITS_MILLISECONDS);
}

uint64_t cnt = 0;

AMS_OSRAM_AS7343 as7343;

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    // 1000000 - ~1.1 sec
    int freqMod = (int)(1000000.0 / 1.1 / DESIRED_FREQ / 20);

    if (!as7343.begin()){
        APP_ERR_PRINT("Could not find AS7343\n");
        while (1) { delay(10); }
    }

    as7343.setATIME(100);
    as7343.setASTEP(999);
    as7343.setGain(AS7343_GAIN_256X);

    //as7343.enableLED(true);
    //as7343.setLEDCurrent(15);

    uint16_t readings[12];

    usb_init();
    while (true) {
        cnt++;

        if (configured && cnt % freqMod == 0) {
            if (!as7343.readAllChannels(readings)){
                APP_ERR_PRINT("Error reading all channels!");
            }

            /*
            APP_PRINT("ADC0/F1 415nm : %d\n", readings[0]);
            APP_PRINT("ADC1/F2 445nm : %d\n", readings[1]);
            APP_PRINT("ADC2/F3 480nm : %d\n", readings[2]);
            APP_PRINT("ADC3/F4 515nm : %d\n", readings[3]);
            APP_PRINT("ADC0/F5 555nm : %d\n", readings[6]);

            APP_PRINT("ADC1/F6 590nm : %d\n", readings[7]);
            APP_PRINT("ADC2/F7 630nm : %d\n", readings[8]);
            APP_PRINT("ADC3/F8 680nm : %d\n", readings[9]);
            APP_PRINT("ADC4/Clear    : %d\n", readings[10]);
            APP_PRINT("ADC5/NIR      : %d\n\n", readings[11]);
            */

            print_val(readings[0]);
            print_to_console((char*)comma);
            print_val(readings[1]);
            print_to_console((char*)comma);
            print_val(readings[2]);
            print_to_console((char*)comma);
            print_val(readings[3]);
            print_to_console((char*)comma);
            print_val(readings[6]);
            print_to_console((char*)comma);
            print_val(readings[7]);
            print_to_console((char*)comma);
            print_val(readings[8]);
            print_to_console((char*)comma);
            print_val(readings[9]);
            print_to_console((char*)endline);

            cnt = 0;
        }
        handle_usb_event();
    }

#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, &IOPORT_CFG_NAME);
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
