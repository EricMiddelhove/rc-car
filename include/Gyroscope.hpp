#include <Arduino.h>
#include <Wire.h>

class Gyro {
 private:
  short int accelerometer[3];  // [accX, accY, accZ]
  short int accelerometer_registers[3] = {0x3B, 0x3C, 0x3D};
  short int gyro[3];  // [gyrX, gyrY, gyrZ]
  short int gyro_registers[3] = {0x43, 0x44, 0x45};

  const short int MPU6050_ADRESS = 0x68;

  const short int PWR_MGMT = 0x6B;

 public:
  Gyro();

  short int* getAccelerometerData();

  short int* getGyroData();

  void sleep();

  void wake();
};
