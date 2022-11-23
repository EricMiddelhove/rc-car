#include "CarState.hpp"

#include "Gyroscope.hpp"

CarState::CarState(Gyro* gyro, short targetCourse) {
  short* gyroData = gyro->getGyroData();
  short* accData = gyro->getAccelerometerData();

  this->xAcc = accData[0];
  this->yAcc = accData[1];
  this->zAcc = accData[2];

  this->xGyro = gyroData[0];
  this->yGyro = gyroData[1];
  this->zGyro = gyroData[2];

  this->targetCourse = targetCourse;
  this->zeroCourseGyroValue = this->zGyro;

  this->course = 0;
}

CarState::CarState(Gyro* gyro) {
  short* gyroData = gyro->getGyroData();
  short* accData = gyro->getAccelerometerData();

  this->xAcc = accData[0];
  this->yAcc = accData[1];
  this->zAcc = accData[2];

  this->xGyro = gyroData[0];
  this->yGyro = gyroData[1];
  this->zGyro = gyroData[2];

  this->targetCourse = targetCourse;

  this->course = map(this->zGyro, zeroCourseGyroValue, 32767, 0, 360);
}

CarState::CarState() {
  // TODO: Adjust Values
}
