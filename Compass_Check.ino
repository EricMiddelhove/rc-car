#include <QMC5883LCompass.h>
QMC5883LCompass compass;
void setup() {
  Serial.begin(9600);
  compass.init();
}
void loop() {
  compass.read();  // Read compass values
  byte a = compass.getAzimuth();
  // Return Azimuth reading
  Serial.print(F("Azimuth: "));
  Serial.println(a);
  byte d = compass.getBearing(a);
  // Output is a value from 0 - 15
  // based on the direction of the bearing / azimuth Serial.print("Direction: ");
  Serial.println(d);
  char compassLetters[3];
  compass.getDirection(compassLetters, a);
  Serial.print(compassLetters[0]);
  Serial.print(compassLetters[1]);
  Serial.println(compassLetters[2]);
  delay(1000);
}
