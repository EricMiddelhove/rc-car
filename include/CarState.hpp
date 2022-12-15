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

  char* getValues();

  int getXAcc();
  int getYAcc();
  int getZAcc();

  int getXGyro();
  int getYGyro();
  int getZGyro();

  int getSteeringPercent();
  int getAcceleratorPercent();

  int getCourse();
  int getTargetCourse();

 private:
  char* values = new char[VALUES_LENGTH];

  int zeroCourseGyroValue;
  Gyro* gyro;
  SteeringWheel* steeringwheel;
  AcceleratorPedal* acceleratorpedal;
};

#endif