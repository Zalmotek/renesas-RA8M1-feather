#include "Particle.h"

#define BUFF_LEN 64

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);
//SYSTEM_MODE(MANUAL);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup() {
  Serial1.begin(115200);
}

int idx;
char buff[BUFF_LEN];
void loop() {
  if (Serial1.available()) {
    idx = 0;
    while (Serial1.available()) {
      buff[idx++] = Serial1.read();
      delay(10);
    }
    Particle.publish("counter", String::format(buff));
  }
}