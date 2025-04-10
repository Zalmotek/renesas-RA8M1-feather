#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(0, 1);  // Rx, Tx

void setup() {
  Serial.begin(115200);

  while (!Serial) {
  }

  if (!SoftSerial.begin(115200, SERIAL_8N1)) {
    Serial.println("Failed to init soft serial");
  }

  // Initial pose - lower and leaning more backward
  moveBody(0.0, 0.0, 150.0, 0.0, 0.0);
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

float movement = 120.00;
float lift = -10.00;
// float lower = 20.0;
// float bend = -0.2;

void loop() {  // run over and over
  if (SoftSerial.available() > 0) {
    // Step 1: Lift and move forward diagonal pair (front-left and rear-right)
    moveLeg("fl", 0.0, movement, lift);
    moveLeg("rr", 0.0, movement, lift);
    // delay(1000);

    moveLeg("fr", 0.0, -movement, lift);
    moveLeg("rl", 0.0, -movement, lift);
    // delay(1000);

    moveLeg("fr", 0.0, movement, lift);
    moveLeg("rl", 0.0, movement, lift);
    // delay(1000);

    moveLeg("fl", 0.0, -movement, lift);
    moveLeg("rr", 0.0, -movement, lift);
    // delay(1000);


    // // Step 2: Lower the lifted legs
    // moveLeg("fl", 0.0, 0.0, lower);
    // moveLeg("rr", 0.0, 0.0, lower);
    // moveLeg("fr", 0.0, 0.0, lower);
    // moveLeg("rl", 0.0, 0.0, lower);

    // Step 3: Shift body weight forward
    // moveBody(0.0, lift, movement, bend, 0.0);

    // // Step 4: Lift and move forward other diagonal pair (front-right and rear-left)
    // moveLeg("fr", 0.0, movement, lift);
    // moveLeg("rl", 0.0, movement, lift);
    // moveLeg("fl", 0.0, 0.0, lift);
    // moveLeg("rr", 0.0, 0.0, lift);

    // // Step 5: Lower the lifted legs
    // moveLeg("fr", 0.0, 0.0, lower);
    // moveLeg("rl", 0.0, 0.0, lower);
    // moveLeg("fl", 0.0, 0.0, lower);
    // moveLeg("rr", 0.0, 0.0, lower);

    // // Step 6: Complete body shift
    // moveBody(0.0, lift, movement, bend, 0.0);

    // // Step 7: Reset body position for next cycle
    // moveBody(0.0, 0.0, movement, bend, 0.0);
    // // delay(1000);

    // delay(50);  // Short pause before next cycle
  }
}

void moveLeg(const char* leg, float x, float y, float z) {
  char cstr[50];
  sprintf(cstr, "F%s tx%.3f ty%.3f tz%.3f \n", leg, x, y, z);
  Serial.write(cstr);
  SoftSerial.write(cstr);
  delay(500);
}

void moveBody(float x, float y, float z, float rx, float ry) {
  char cstr[100];
  sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", x, y, z, rx, ry, 0.0, 120.0, 120.0);
  Serial.write(cstr);
  SoftSerial.write(cstr);
  delay(500);
}