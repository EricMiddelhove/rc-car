#include "Compass.hpp"

Compass::Compass() {
  // Set up continuous measurement mode
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x0B);
  Wire.write(0x01);
  Wire.endTransmission(true);

  // Configure measurement rate
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x09);
  Wire.write(0b1001);
  Wire.endTransmission(true);
}

int Compass::getAzimuth() {
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(axis_registers[0]);
  Wire.endTransmission(false);

  Wire.requestFrom(COMPASS_ADDRESS, 6, true);

  int x, y;
  byte read1, read2;

  read1 = Wire.read();
  read2 = Wire.read();
  x = read2 << 8 | read1;

  read1 = Wire.read();
  read2 = Wire.read();
  y = read2 << 8 | read1;

  Wire.endTransmission(true);

  int azimuth = atan2(x, y) * 180 / PI;

  if (azimuth < 0) {
    azimuth += 360;
  }

  azimuth = 360 - azimuth;

  return azimuth;
}