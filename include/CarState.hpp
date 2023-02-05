#ifndef CarState_hpp
#define CarState_hpp

#include "AcceleratorPedal.hpp"
#include "Arduino.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "QMC5883LCompass.h"
#include "SteeringWheel.hpp"

class CarState {
 public:
  CarState(MPU6050* mpu, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal, QMC5883LCompass* compass);
  CarState();
  const static int VALUES_LENGTH = 26;

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

  void getYawPitchRoll(int16_t* ypr);

  static void average(CarState* states[], int length, CarState* result);

 private:
  void configureMPU();

  byte* values = new byte[VALUES_LENGTH];

  int initialCourse;

  int zeroCourseGyroValue;

  MPU6050* mpu;
  SteeringWheel* steeringwheel;
  AcceleratorPedal* acceleratorpedal;
  QMC5883LCompass* compass;

  // MPU Control
  Quaternion* q;
  VectorFloat* gravity;

  bool dmpReady = false;   // set true if DMP init was successful
  uint8_t mpuIntStatus;    // holds actual interrupt status byte from MPU
  uint8_t devStatus;       // return status after each device operation (0 = success, !0 = error)
  uint16_t packetSize;     // expected DMP packet size (default is 42 bytes)
  uint16_t fifoCount;      // count of all bytes currently in FIFO
  uint8_t fifoBuffer[64];  // FIFO storage buffer
};

#endif