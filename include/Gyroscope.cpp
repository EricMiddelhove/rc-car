#include "Gyroscope.hpp"

#include <Arduino.h>
#include <Wire.h>

Gyro::Gyro() {
  wake();
  configure();

  return;
}

Gyro::~Gyro() {
  Wire.endTransmission(true);
  return;
}

int* Gyro::getAccelerometerData() {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(accelerometer_registers[0]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 6, true);

  for (int i = 0; i < 3; i++) {
    accelerometer[i] = Wire.read() << 8 | Wire.read();
  }

  return accelerometer;
}

int* Gyro::getGyroData() {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(gyro_registers[0]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 6, true);

  for (int i = 0; i < 3; i++) {
    gyro[i] = Wire.read() << 8 | Wire.read();
  }

  return gyro;
}

int Gyro::getGyroDataOfAxis(char axis) {
  axis = axis | 0x20;  // convert to lowercase

  byte ident = axis - 120;  // convert /x/y/z/ to /0/1/2/

  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(gyro_registers[ident]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 2, true);

  int result = Wire.read() << 8 | Wire.read();

  return result;
}

void Gyro::getAccelerometerData(byte* results) {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(accelerometer_registers[0]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 6, true);

  for (int i = 0; i < 6; i += 2) {
    results[i] = Wire.read();
    results[i + 1] = Wire.read();
  }

  return;
}

void Gyro::getGyroData(byte* results) {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(gyro_registers[0]);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADRESS, 6, true);

  for (int i = 0; i < 6; i += 2) {
    results[i] = Wire.read();
    results[i + 1] = Wire.read();
  }

  return;
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

void Gyro::configure() {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(0x1B);  // Gyro config
  Wire.write(0x00);  // +/- 250 degrees per second full scale
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(0x1B);  // Accel config
  Wire.endTransmission(true);

  Wire.requestFrom(MPU6050_ADRESS, 1, true);
  byte result = Wire.read();

  // Serial.print(F("Accel config: "));
  Serial.println(result, BIN);

  return;
}

void Gyro::trim() {
  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(0x10);
  Wire.endTransmission(false);

  Wire.beginTransmission(MPU6050_ADRESS);
  Wire.write(0b00011111);

  return;
}