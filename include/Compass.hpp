#ifndef COMPASS_HPP
#define COMPASS_HPP

#include "Arduino.h"
#include "Wire.h"

#define COMPASS_ADDRESS 0x0D

class Compass {
 public:
  Compass();
  int getCourse();
  void setZeroCourse(int course);
  int getZeroCourse();
  int getAxisValue(char axis);
  int getAzimuth();

 private:
  byte axis_registers[3] = {0x00, 0x02, 0x04};  // x, y, z

  int zeroCourse;

  

};

#endif