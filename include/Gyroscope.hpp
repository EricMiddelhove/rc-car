#ifndef Gyroscope_hpp
#define Gyroscope_hpp

#include <Arduino.h>
#include <Wire.h>

class Gyro {
 private:
  int accelerometer[3];  // [accX, accY, accZ]
  byte accelerometer_registers[3] = {0x3B, 0x3D, 0x3F};
  int gyro[3];  // [gyrX, gyrY, gyrZ]
  byte gyro_registers[3] = {0x43, 0x45, 0x47};

  const byte MPU6050_ADRESS = 0x68;

  const byte PWR_MGMT = 0x6B;

  void configure();

 public:
  Gyro();

  int* getAccelerometerData();

  int* getGyroData();

  int getGyroDataOfAxis(char axis);

  void getGyroData(char* results);
  void getAccelerometerData(char* results);

  void sleep();

  void wake();

  void trim();
};

#endif
