#include "CarState.hpp"

CarState::CarState(MPU6050* mpu, SteeringWheel* steeringwheel, AcceleratorPedal* acceleratorpedal, QMC5883LCompass* compass) {
  this->mpu = mpu;
  this->steeringwheel = steeringwheel;
  this->acceleratorpedal = acceleratorpedal;
  this->compass = compass;

  this->initialCourse = compass->getAzimuth();

  this->configureMPU();

  this->refresh();
}

CarState::CarState() {
}

void CarState::configureMPU() {
  mpu->initialize();
  devStatus = mpu->dmpInitialize();

  // supply own gyro offsets here, scaled for min sensitivity
  mpu->setXGyroOffset(220);
  mpu->setYGyroOffset(76);
  mpu->setZGyroOffset(-85);
  mpu->setZAccelOffset(1788);

  if (devStatus == 0) {
    mpu->CalibrateAccel(6);
    mpu->CalibrateGyro(6);
    mpu->PrintActiveOffsets();

    mpu->setDMPEnabled(true);
    packetSize = mpu->dmpGetFIFOPacketSize();
  } else {
    Serial.print("MPU6050 DMP Initialization failed (code ");
    Serial.print(devStatus);
    Serial.println(")");
  }
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

int CarState::getGlobalCourse() {
  int v = (values[16] << 8 | values[17]);
  return v;
}

int CarState::getLocalCourse() {
  int v = getGlobalCourse();

  v = v - initialCourse;
  if (v < 0) {
    v = 360 + v;
  }
  return v;
}

int CarState::getTargetCourse() {
  int v = (values[18] << 8 | values[19]);
  return v;
}

void CarState::setTargetCourse(int course) {
  values[19] = course & 0xFF;
  values[18] = (course >> 8) & 0xFF;
}

void CarState::getYawPitchRoll(int16_t* ypr) {
  ypr[0] = (values[18] << 8 | values[19]);  // Yaw
  ypr[1] = (values[20] << 8 | values[21]);  // Pitch
  ypr[2] = (values[22] << 8 | values[23]);  // Roll
}

void CarState::refresh() {
  // Serial.print("\tCarState::refresh()");
  // gyro->getAccelerometerData(values);  // initialises 6 bytes
  for (int i = 0; i < 6; i++) {  // Mocks accelerometer data
    values[i] = values[i] & 0x00;
  }

  // gyro->getGyroData(values + 6);       // initialises 6 bytes
  for (int i = 0; i < 6; i++) {  // Mocks gyro data
    values[i] = values[i] & 0x00;
  }

  int steeringPercent = steeringwheel->getSteeringPercent();
  values[13] = steeringPercent & 0xFF;
  values[12] = (steeringPercent >> 8) & 0xFF;

  int acceleratorPercent = acceleratorpedal->getAcceleratorPercent();
  values[15] = acceleratorPercent & 0xFF;
  values[14] = (acceleratorPercent >> 8) & 0xFF;

  // compass->read();
  // int course = compass->getAzimuth();
  int course = 0;
  values[17] = (course & 0xFF);
  values[16] = (course >> 8) & 0xFF;

  float ypr[3];
  mpu->dmpGetQuaternion(q, fifoBuffer);
  mpu->dmpGetGravity(gravity, q);
  mpu->dmpGetYawPitchRoll(ypr, q, gravity);

  float yaw = ypr[0] * 180 / M_PI;
  float pitch = ypr[1] * 180 / M_PI;
  float roll = ypr[2] * 180 / M_PI;

  Serial.print("\tCarState::refresh() - Yaw: ");
  Serial.print(yaw);
  values[19] = (int)yaw & 0xFF;
  values[18] = ((int)yaw >> 8) & 0xFF;

  values[21] = (int)pitch & 0xFF;
  values[20] = ((int)pitch >> 8) & 0xFF;

  values[23] = (int)roll & 0xFF;
  values[22] = ((int)roll >> 8) & 0xFF;
}

byte* CarState::getValues() {
  return this->values;
}

void CarState::average(CarState* states[], int length, CarState* result) {
  for (int j = 0; j < length; j++) {
    CarState* currentStateInIteration = states[j];
    for (int i = 0; i < VALUES_LENGTH; i += 2) {
      result->values[i] *= currentStateInIteration->values[i];
    }
  }

  for (int i = 0; i < VALUES_LENGTH; i += 2) {
    int avg = result->values[i] / length;
    result->values[i] = avg & 0xFF;
  }
}