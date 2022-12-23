#ifndef COMPASS_HPP
#define COMPASS_HPP

#include "Arduino.h"
#include "Wire.h"

#define COMPASS_ADDRESS 0x0D

class Compass {
 public:
  Compass();
  int getAzimuth();

 private:
  byte axis_registers[3] = {0x00, 0x02, 0x04};  // x, y, z

  int zeroCourse;
};

#endif