#include "main_thread.h"
#include <Arduino.h>
#include <Wire.h>

/* Main Thread entry function */
/* pvParameters contains TaskHandle_t */
void main_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    Serial1.begin(115200);
    APP_PRINT("\nI2C Scanner");
    Wire.begin();

    while (true) {
        byte error, address;
        int nDevices;

        APP_PRINT("Scanning...");

        nDevices = 0;
        for(address = 1; address < 127; address++ )
        {
          // The i2c_scanner uses the return value of
          // the Write.endTransmisstion to see if
          // a device did acknowledge to the address.
          Wire.beginTransmission(address);
          error = Wire.endTransmission();

          if (error == 0)
          {
            APP_PRINT("I2C device found at address 0x");
            if (address<16)
              APP_PRINT("0");
            APP_PRINT("%d",address,HEX);
            APP_PRINT("  !");

            nDevices++;
          }
          else if (error==4)
          {
            APP_PRINT("Unknown error at address 0x");
            if (address<16)
              APP_PRINT("0");
            APP_PRINT("%d",address,HEX);
          }
        }
        if (nDevices == 0)
          APP_PRINT("No I2C devices found\n");
        else
          APP_PRINT("done\n");

        delay(5000);           // wait 5 seconds for next scan
        vTaskDelay(100);
    }
}
