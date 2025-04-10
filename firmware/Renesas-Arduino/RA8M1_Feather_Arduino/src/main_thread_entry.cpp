#include "main_thread.h"
#include <Arduino.h>

/* Main Thread entry function */
/* pvParameters contains TaskHandle_t */
void main_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    Serial.begin(115200);

    while (true) {
        vTaskDelay(1);
    }
}
