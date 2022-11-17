#include "Gyroscope.hpp"

#include <Arduino.h>
#include <Wire.h>

Gyro::Gyro() {
  pinMode(LED_BUILTIN, OUTPUT);
  wake();
  digitalWrite(LED_BUILTIN, HIGH);
  return;
}

short int* Gyro::getAccelerometerData() {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(accelerometer_registers[0]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 6, true);

  for (int i = 0; i < 3; i++) {
    accelerometer[i] = Wire.read() << 8 | Wire.read();
  }

  return accelerometer;
}

short int* Gyro::getGyroData() {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(gyro_registers[0]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 6, true);

  for (int i = 0; i < 3; i++) {
    gyro[i] = Wire.read() << 8 | Wire.read();
  }

  return gyro;
}

void Gyro::sleep() {
  Wire.begin();
  Wire.beginTransmission(MPU6050_ADRESS);  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                        // PWR_MGMT_1 register
  Wire.write(1);                           // set to sleep (sleeps the MPU-6050)
  Wire.endTransmission(true);

  return;
}

void Gyro::wake() {
  Wire.begin();
  Wire.beginTransmission(MPU6050_ADRESS);  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                        // PWR_MGMT_1 register
  Wire.write(0);                           // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  return;
}
