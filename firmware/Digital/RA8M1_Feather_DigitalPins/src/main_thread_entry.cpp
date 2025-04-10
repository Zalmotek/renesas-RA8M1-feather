#include "main_thread.h"
#include <Arduino.h>

// Array of LED pins
int ledPins[] = {5, 6, 9, 10, 11, 12, 13, 14};
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Calculate the number of LEDs
int blinkDelay = 500; // Delay in milliseconds

/* Main Thread entry function */
/* pvParameters contains TaskHandle_t */
void main_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    Serial1.begin(115200);
    // Initialize all pins as outputs
    for (int i = 0; i < numLeds; i++) {
      pinMode(ledPins[i], OUTPUT);
    }

    while (true) {
        // Blink each LED in sequence
        for (int i = 0; i < numLeds; i++) {
          APP_PRINT("%d\n",ledPins[i]);
          digitalWrite(ledPins[i], HIGH); // Turn LED on
          delay(blinkDelay);             // Wait
          digitalWrite(ledPins[i], LOW); // Turn LED off
        }

        // Optional: Add a delay before restarting the sequence
        delay(1000);
        vTaskDelay(100);
    }
}
