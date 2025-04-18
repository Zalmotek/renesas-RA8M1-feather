#include "genieArduinoDEV.h"
#include "tmf8828.h"
#include "AMS_OSRAM_AS7343.h"
#include "as7331.h"
#include "digital.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

#define RESET_PIN 0x010C    //D10


// Specify sensor parameters //
MMODE   mmode = AS7331_CONT_MODE;  // choices are modes are CONT, CMD, SYNS, SYND
CCLK    cclk  = AS7331_1024;      // choices are 1.024, 2.048, 4.096, or 8.192 MHz
uint8_t sb    = 0x01;             // standby enabled 0x01 (to save power), standby disabled 0x00
uint8_t breakTime = 40;           // sample timeMs == 8 us x breaktimeMs (0 - 255, or 0 - 2040 us range), CONT or SYNX modes

uint8_t gain = 8; // ADCGain = 2^(11-gain), by 2s, 1 - 2048 range,  0 < gain = 11 max, default 10
uint8_t timeMs = 9; // 2^time in ms, so 0x07 is 2^6 = 64 ms, 0 < time = 15 max, default  6

// sensitivities at 1.024 MHz clock
float lsbA = 304.69f / ((float)(1 << (11 - gain))) / ((float)(1 << timeMs)/1024.0f) / 1000.0f;  // uW/cm^2
float lsbB = 398.44f / ((float)(1 << (11 - gain))) / ((float)(1 << timeMs)/1024.0f) / 1000.0f;
float lsbC = 191.41f / ((float)(1 << (11 - gain))) / ((float)(1 << timeMs)/1024.0f) / 1000.0f;


uint16_t tempData= 0, UVAData = 0, UVBData = 0, UVCData = 0, allData[4] = {0, 0, 0, 0};
float temp_C = 0;
int status;

I2Cdev i2c_0;
AS7331 AS7331(&i2c_0);

AMS_OSRAM_AS7343 as7343;

int obj0conf[8][8] = {0}, obj0dist[8][8] = {0}, obj1conf[8][8] = {0}, obj1dist[8][8] = {0};

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
    Serial1.begin(115200);
    delay(500);
    tick += 500;
    Genie genie(&Serial1);
    delay(500);
    tick += 500;

    AS7331.powerUp();
    AS7331.reset();
    delay(100);
    uint8_t AS7331_ID = AS7331.getChipID();
    //APP_PRINT("ID: %d\n", AS7331_ID);


    // check if AS7331 has acknowledged
    if(AS7331_ID == 0x21)  {
        AS7331.setConfigurationMode();
        AS7331.init(mmode, cclk, sb, breakTime, gain, timeMs);
        delay(100); // let sensor settle
        AS7331.setMeasurementMode();
    }
    else {
        APP_ERR_PRINT("Wrong id: %d\n", AS7331_ID);
    }



    if (!as7343.begin()){
        APP_ERR_PRINT("Could not find AS7343\n");
        while (1) { delay(10); }
    }

    as7343.setATIME(100);
    as7343.setASTEP(999);
    as7343.setGain(AS7343_GAIN_256X);



    TMF8828 sensor;
    sensor.factoryCalibration(0); //must be before startMeasuring
    sensor.startMeasuring();


    // Sensor initialisation must(?) be before display init
    R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(RESET_PIN, LOW);
    delay(100);
    digitalWrite(RESET_PIN, HIGH);
    delay(500);

    uint16_t readings[12];

    tick += 1500;

    if (genie.Begin()) {
        for (int i = 0; i < 3; i++) {
            genie.WriteStr(0, (char*)"");
            delay(500);
            tick += 500;
            genie.WriteStr(0, (char*)"alo");
            delay(500);
            tick += 500;
        }
        while (true) {

            status = AS7331.getStatus();
            //APP_PRINT("Current status: %d\n", status);

            if (status & 0x0008) {
                AS7331.readAllData(allData); // burst read data in one I2C transaction takes 281 us
                tempData = allData[0];
                UVAData  = allData[1];
                UVBData  = allData[2];
                UVCData  = allData[3];
                temp_C = tempData * 0.05f - 66.9f;

                genie.WriteStr(0, UVAData * lsbA);
                genie.WriteStr(1, UVBData * lsbB);
                genie.WriteStr(2, UVCData * lsbC);
                genie.WriteStr(3, temp_C);

                /*
                APP_PRINT("Raw counts\n");
                APP_PRINT("AS7331 UVA = %d\n", UVAData);
                APP_PRINT("AS7331 UVB = %d\n", UVBData);
                APP_PRINT("AS7331 UVC = %d\n\n", UVCData);

                APP_PRINT("Scaled UV data\n");
                APP_PRINT("AS7331 UVA (uW/cm^2)= %d", (int)((float)(UVAData)*lsbA));
                APP_PRINT(".%d\n", (int)((float)(UVAData) * lsbA * 100 ) % 100);
                APP_PRINT("AS7331 UVB (uW/cm^2)= %d", (int)((float)(UVBData)*lsbB));
                APP_PRINT(".%d\n", (int)((float)(UVBData) * lsbB * 100) % 100);
                APP_PRINT("AS7331 UVC (uW/cm^2)= %d", (int)((float)(UVCData)*lsbC));
                APP_PRINT(".%d\n\n", (int)((float)(UVCData) * lsbC * 100)  % 100);

                temp_C = tempData * 0.05f - 66.9f;
                APP_PRINT("AS7331 Temperature = %d", (int)temp_C);
                APP_PRINT(".%d C\n\n", (int)((float)(temp_C) * 100)  % 100);
                */
            }
            delay(100);
            tick += 100;




            if (!as7343.readAllChannels(readings)){
                APP_ERR_PRINT("Error reading all channels!");
            }
            else {
                genie.WriteStr(4, readings[0]);
                genie.WriteStr(5, readings[1]);
                genie.WriteStr(6, readings[2]);
                genie.WriteStr(7, readings[3]);
                genie.WriteStr(8, readings[6]);
                genie.WriteStr(9, readings[7]);
                genie.WriteStr(10, readings[8]);
                genie.WriteStr(11, readings[9]);
                genie.WriteStr(12, readings[10]);
                genie.WriteStr(13, readings[11]);

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

            }
            delay(100);
            tick += 130;



            int conf[32], dist[32];

            if (sensor.update(conf, dist)) {

                //for (int i = 0; i < 32; i++) {
                //    APP_PRINT("nr: %d, conf: %d, dist: %d\n", i, conf[i], dist[i]);
                //}
                //APP_PRINT("\n");


                int idx = 14;
                for (int i = 0; i < 8; i++) {
                    if (dist[i] > 0) {
                        genie.WriteStr(idx, dist[i]);
                        idx++;
                        if (idx == 17) {
                            break;
                        }
                    }
                }
                idx = 19;
                for (int i = 16; i >= 8; i--) {
                    if (dist[i] > 0) {
                        genie.WriteStr(idx, dist[i]);
                        idx--;
                        if (idx == 16) {
                            break;
                        }
                    }
                }
            }

            delay(100);
            tick += 150;
        }
    }
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
