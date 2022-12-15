#include "CarState.hpp"

#include "Gyroscope.hpp"

CarState::CarState(Gyro* gyro, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal) {
  this->gyro = gyro;
  this->steeringwheel = steeringwheel;
  this->acceleratorpedal = acceleratorpedal;

  this->refresh();
}

int CarState::getXAcc() {
  int v = (values[0] << 8 | values[1]);
  return v;
}

int CarState::getYAcc() {
  int v = (values[2] << 8 | values[3]);
  return v;
}

int CarState::getZAcc() {
  int v = (values[4] << 8 | values[5]);
  return v;
}

int CarState::getXGyro() {
  int v = (values[6] << 8 | values[7]);
  return v;
}

int CarState::getYGyro() {
  int v = (values[8] << 8 | values[9]);
  return v;
}

int CarState::getZGyro() {
  int v = (values[10] << 8 | values[11]);
  return v;
}

int CarState::getSteeringPercent() {
  int v = (values[12] << 8 | values[13]);
  return v;
}

int CarState::getAcceleratorPercent() {
  int v = (values[14] << 8 | values[15]);
  return v;
}

int CarState::getCourse() {
  int v = (values[16] << 8 | values[17]);
  return v;
}

int CarState::getTargetCourse() {
  int v = (values[18] << 8 | values[19]);
  return v;
}

void CarState::refresh() {
  gyro->getGyroData(values);               // initialises 6 bytes
  gyro->getAccelerometerData(values + 6);  // initialises 6 bytes

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