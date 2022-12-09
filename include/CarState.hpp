#ifndef CarState_hpp
#define CarState_hpp

#include "AcceleratorPedal.hpp"
#include "Arduino.h"
#include "Gyroscope.hpp"
#include "SteeringWheel.hpp"

class CarState {
 public:
  short xAcc;
  short yAcc;
  short zAcc;
  short xGyro;
  short yGyro;
  short zGyro;

  int steeringPercent;
  int acceleratorPercent;

  short course;
  short targetCourse;

  CarState(Gyro* gyro, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal);
  CarState(Gyro* gyro);
  CarState();

  String getCSVLine();

 private:
  short zeroCourseGyroValue;
};

#endif