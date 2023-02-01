#ifndef CarState_hpp
#define CarState_hpp

#include "AcceleratorPedal.hpp"
#include "Arduino.h"
// #include "Compass.hpp"
#include "Gyroscope.hpp"
#include "QMC5883LCompass.h"
#include "SteeringWheel.hpp"

class CarState {
 public:
  CarState(Gyro* gyro, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal, QMC5883LCompass* compass);
  CarState();
  const static int VALUES_LENGTH = 20;

  void refresh();

  byte* getValues();

  int getXAcc();
  int getYAcc();
  int getZAcc();

  int getXGyro();
  int getYGyro();
  int getZGyro();

  int getSteeringPercent();
  int getAcceleratorPercent();

  int getGlobalCourse();
  int getLocalCourse();
  int getTargetCourse();
  void setTargetCourse(int course);

  static void average(CarState* states[], int length, CarState* result);

 private:
  byte* values = new byte[VALUES_LENGTH];

  int initialCourse;

  int zeroCourseGyroValue;
  Gyro* gyro;
  SteeringWheel* steeringwheel;
  AcceleratorPedal* acceleratorpedal;
  QMC5883LCompass* compass;
};

#endif