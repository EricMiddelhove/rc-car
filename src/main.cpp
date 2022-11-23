#include <Arduino.h>

#include "AcceleratorPedal.cpp"
#include "CarState.cpp"
#include "Gyroscope.cpp"
#include "SteeringWheel.cpp"
#define DEBUG_SD_ONLY 1
#define DEBUG_FULL 2
#define DEBUG_OFF 0

#define DEBUG_MODE DEBUG_FULL

#if DEBUG_MODE > 0
#include "Logger.cpp"
Logger* logger = NULL;
#endif

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;

void setup() {
// put your setup code here, to run once:
#if (DEBUG_MODE > 1)
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
#endif

  SteeringWheel sw(2, 9);
  steeringWheel = &sw;

  AcceleratorPedal ap(3, 10);
  acceleratorPedal = &ap;

  Gyro gyro;
  gyro.wake();

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

#if (DEBUG_MODE > 0)
  logger = new Logger();
  Logger lg;
  logger = &lg;

  logger->log("Logger Initialized");
  logger->log("Log Ending");
#endif

  CarState initialCarState(&gyro, 0);

#if (DEBUG_MODE > 0)
  logger->log(initialCarState.getCSVLine());
  delete logger;
#endif

  delay(3000);
}

void loop() {
  // Serial.print("Steering: " + String(rawSteeringInputPWM) + "\t");
  // Serial.print("Acceleration: " + String(rawAcceleratorInputPWM) + "\n");
}