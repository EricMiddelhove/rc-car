#include "CarState.hpp"

#include "Gyroscope.hpp"

CarState::CarState(Gyro* gyro, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal) {
  this->gyro = gyro;
  this->steeringwheel = steeringwheel;
  this->acceleratorpedal = acceleratorpedal;

  this->refresh();

  // this->xAcc = &values[0];
  // this->yAcc = &values[1];
  // this->zAcc = &values[2];
  // this->xGyro = &values[3];
  // this->yGyro = &values[4];
  // this->zGyro = &values[5];
  // this->targetCourse = &values[6];
  // this->course = &values[7];
  // this->steeringPercent = &values[8];
  // this->acceleratorPercent = &values[9];
}

void CarState::refresh() {
  int* gyroData = gyro->getGyroData();
  int* accData = gyro->getAccelerometerData();

  accData[0] = -accData[0];

  values[1] = (accData[0] & 0xFF);
  values[0] = (accData[0] >> 8) & 0xFF;

  values[3] = accData[1] & 0xFF;
  values[2] = accData[1] >> 8 & 0xFF;

  values[5] = accData[2] & 0xFF;
  values[4] = accData[2] >> 8 & 0xFF;

  values[7] = gyroData[0] & 0xFF;
  values[6] = gyroData[0] >> 8 & 0xFF;

  values[9] = gyroData[1] & 0xFF;
  values[8] = gyroData[1] >> 8 & 0xFF;

  values[11] = gyroData[2] & 0xFF;
  values[10] = gyroData[2] >> 8 & 0xFF;

  int steeringPercent = steeringwheel->getSteeringPercent();
  values[13] = steeringPercent & 0xFF;
  values[12] = (steeringPercent >> 8) & 0xFF;

  int acceleratorPercent = acceleratorpedal->getAcceleratorPercent();
  values[15] = acceleratorPercent & 0xFF;
  values[14] = (acceleratorPercent >> 8) & 0xFF;

  int course = 0;
  values[17] = course & 0xFF;
  values[16] = (course >> 8) & 0xFF;

  int targetCourse = 0;
  values[19] = targetCourse & 0xFF;
  values[18] = (targetCourse >> 8) & 0xFF;
}

CarState::CarState() {
  // TODO: Adjust Values
}

char* CarState::getValues() {
  return this->values;
}