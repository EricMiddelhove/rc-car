#ifndef CarState_hpp
#define CarState_hpp

#include "AcceleratorPedal.hpp"
#include "Arduino.h"
#include "Gyroscope.hpp"
#include "SteeringWheel.hpp"

class CarState {
 public:
  CarState(Gyro* gyro, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal);
  CarState();
  const int VALUES_LENGTH = 20;

  void refresh();

  // String getCSVLine();
  String getCSVHeader();

  char* getValues();

  int* xAcc;
  int* yAcc;
  int* zAcc;
  int* xGyro;
  int* yGyro;
  int* zGyro;

  int* steeringPercent;
  int* acceleratorPercent;

  int* course;
  int* targetCourse;

 private:
  char* values = new char[VALUES_LENGTH];

  int zeroCourseGyroValue;
  Gyro* gyro;
  SteeringWheel* steeringwheel;
  AcceleratorPedal* acceleratorpedal;
};

#endif