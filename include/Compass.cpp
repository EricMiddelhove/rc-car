#include "Compass.hpp"

Compass::Compass() {
  // module.setCalibration(-975, 1352, -1900, 73, -1355, 0);
  // module.setADDR(COMPASS_ADDRESS);
  // module.setMode(0b01000000, 0b00010000, 0b00000100, 0b00000001);
}

int Compass::getAzimuth() {
  int azimuth = module.getAzimuth();
  return azimuth;
}