#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(0, 1);  // Rx, Tx

void setup() {
  Serial.begin(115200);

  while (!Serial) {
  }

  if (!SoftSerial.begin(115200, SERIAL_8N1)) {
    Serial.println("Failed to init soft serial");
  }

  // Initial pose - lower and leaning more forward
  moveBody(0.0, 0.0, 150.0, -0.1, 0.0);
  delay(5000);
  Serial.println(SoftSerial);
}

float tx, ty, tz;
float rx, ry, rz;
float sx, sy;

char c[20] = "fl";  // Ffl, Ffr, Frl, Frr
char cstr[50];

int StringCount = 0;
String strs[8];
String incomingText;
int dalayVal = 60;

void loop() {  // run over and over
  if (SoftSerial.available() > 0) {
    // Step 1: Lift and move forward diagonal pair (front-left and rear-right)
    moveLeg("fl", 0.0, 120.0, -20.0);
    moveLeg("rr", 0.0, 120.0, -20.0);
    moveLeg("fr", 0.0, 0.0, -20.0);
    moveLeg("rl", 0.0, 0.0, -20.0);

    // Step 2: Lower the lifted legs
    moveLeg("fl", 0.0, 0.0, 20.0);
    moveLeg("rr", 0.0, 0.0, 20.0);
    moveLeg("fr", 0.0, 0.0, 20.0);
    moveLeg("rl", 0.0, 0.0, 20.0);

    // Step 3: Shift body weight forward
    moveBody(0.0, -50.0, 130.0, -0.1, 0.0);

    // Step 4: Lift and move forward other diagonal pair (front-right and rear-left)
    moveLeg("fr", 0.0, 120.0, -20.0);
    moveLeg("rl", 0.0, 120.0, -20.0);
    moveLeg("fl", 0.0, 0.0, -20.0);
    moveLeg("rr", 0.0, 0.0, -20.0);

    // Step 5: Lower the lifted legs
    moveLeg("fr", 0.0, 0.0, 20.0);
    moveLeg("rl", 0.0, 0.0, 20.0);
    moveLeg("fl", 0.0, 0.0, 20.0);
    moveLeg("rr", 0.0, 0.0, 20.0);

    // // Step 6: Complete body shift
    moveBody(0.0, -50.0, 130.0, 0.1, 0.0);

    // Step 7: Reset body position for next cycle
    // moveBody(0.0, 0.0, 150.0, -0.1, 0.0);
  }
}

void moveLeg(const char* leg, float x, float y, float z) {
  char cstr[50];
  sprintf(cstr, "F%s tx%.3f ty%.3f tz%.3f \n", leg, x, y, z);
  Serial.write(cstr);
  SoftSerial.write(cstr);
  delay(dalayVal);
}

void moveBody(float x, float y, float z, float rx, float ry) {
  char cstr[100];
  sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", x, y, z, rx, ry, 0.0, 100.0, 100.0);
  Serial.write(cstr);
  SoftSerial.write(cstr);
  delay(dalayVal);
}