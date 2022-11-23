#ifndef CarState_hpp
#define CarState_hpp

#include "Arduino.h"
#include "Gyroscope.hpp"

class CarState {
 public:
  short xAcc;
  short yAcc;
  short zAcc;
  short xGyro;
  short yGyro;
  short zGyro;

  byte steeringAngle;
  byte acceleratorPercent;

  short course;
  short targetCourse;

  CarState(Gyro* gyro, short targetCourse);
  CarState(Gyro* gyro);
  CarState();

  String getCSVLine();

 private:
  short zeroCourseGyroValue;
};

#endif