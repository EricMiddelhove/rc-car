#ifndef COMPASS_HPP
#define COMPASS_HPP

#include "Arduino.h"
// #include "QMC5883LCompass.h"
#include "Wire.h"

#define COMPASS_ADDRESS 0x0D

class Compass {
 public:
  Compass();
  int getAzimuth();

 private:
  // QMC5883LCompass module;

  int zeroCourse;
};

#endif