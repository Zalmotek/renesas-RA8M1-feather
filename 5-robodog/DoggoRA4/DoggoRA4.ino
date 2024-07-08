#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(0, 1);  // Rx, Tx

void setup() {
  Serial.begin(115200);

  while (!Serial) {
  }

  if (!SoftSerial.begin(115200, SERIAL_8N1)) {
    Serial.println("Failed to init soft serial");
  }

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

void loop() {  // run over and over
  if (SoftSerial.available() > 0) {
    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 90.0, 0.0, 0.0, 0.0, 40.0, 40.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(3000);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 120.0, 0.1, 0.0, 0.0, 60.0, 60.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.2, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.3, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.4, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.5, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.6, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.5, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.4, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.3, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.2, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);

    sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", 0.0, 0.0, 160.0, 0.1, 0.0, 0.0, 80.0, 80.0);
    Serial.write(cstr);
    SoftSerial.write(cstr);
    delay(300);
  }
}


  // if (Serial.available() > 0) {
  //   incomingText = Serial.readString();  // read the incoming byte:
  //   Serial.println(incomingText);

  //   // Split the string into substrings
  //   while (incomingText.length() > 0) {
  //     int index = incomingText.indexOf(' ');
  //     if (index == -1)  // No space found
  //     {
  //       strs[StringCount++] = incomingText;
  //       break;
  //     } else {
  //       strs[StringCount++] = incomingText.substring(0, index);
  //       incomingText = incomingText.substring(index + 1);
  //     }
  //   }
  //   StringCount = 0;

  //   tx = strs[0].toFloat();
  //   ty = strs[1].toFloat();
  //   tz = strs[2].toFloat();

  //   rx = strs[3].toFloat();
  //   ry = strs[4].toFloat();
  //   rz = strs[5].toFloat();

  //   sx = strs[6].toFloat();
  //   sy = strs[7].toFloat();

  //   sprintf(cstr, "Ffl tx%.3f ty%.3f tz%.3f \n", tx, ty, tz);
  //   sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", tx, ty, tz, rx, ry, rz,
  //           sx, sy);
  //   Serial.write(cstr);
  // }

  // tx = 0;     // max 210
  // ty = 0;     // max 210
  // tz = 90;    // max 210
  // rx = 0;     // max 1 - se apleaca sa manance
  // ry = 0;     // max 1 - se apleaca pe picior stanga dreapta
  // rz = 0;     // max 1 -  se uita peste umar stanga dreapta
  // sx = 90;    // max 120
  // sy = 90;    // max 120

  // sprintf(cstr, "P tx%.3f ty%.3f tz%.3f rx%.3f ry%.3f rz%.3f sx%.3f sy%.3f\n", tx, ty, tz, rx, ry, rz,
  //         sx, sy);

// String line = SoftSerial.read();
// line.trim();

// char buffer[1024];
// line.toCharArray(buffer, sizeof(buffer));

// if (buffer[0] == 'F' && buffer[1] == 'F') {
//   float flx, fly, flz, frx, fry, frz, rrx, rry, rrz, rlx, rly, rlz;
//   sscanf(buffer, "FF flx%f fly%f flz%f frx%f fry%f frz%f rrx%f rry%f rrz%f rlx%f rly%f rlz%f", &flx, &fly,
//          &flz, &frx, &fry, &frz, &rrx, &rry, &rrz, &rlx, &rly, &rlz);
// }

// Serial.print("pico says: ");
// Serial.println(SoftSerial.read());
