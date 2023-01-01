
#include "AcceleratorPedal.hpp"

#include "Servo.h"

int accSampleNumber = 0;
int accSampleSum = 0;

int manualAccelerationInputCounter = 0;
int acceleratorPulseCounter = 0;

void fallingAcceleratorPWMPulse() {
  acceleratorPulseCounter++;
  if (acceleratorPulseCounter > 20) {
    acceleratorPulseCounter = 0;
    manualAccelerationInputCounter = 0;
  }

  int currentTime = micros();
  int pulseWidth = currentTime - acceleratorPreviousTime;

  if (pulseWidth < RAW_NO_ACCELERATOR - 100 || pulseWidth > RAW_NO_ACCELERATOR + 100) {
    manualAccelerationInputCounter++;

    if (manualAccelerationInputCounter > 5) {
      Serial.println("Manual Accelerator Detected");
      acceleratorIsManual = true;
      manualAccelerationInputCounter = 0;
    }
  } else {
    acceleratorIsManual = false;
  }

  accSampleSum += pulseWidth;
  accSampleNumber++;

  if (accSampleNumber >= ACC_INPUT_SAMPLE_SIZE) {
    rawAcceleratorInputPWM = accSampleSum / ACC_INPUT_SAMPLE_SIZE;
    accSampleNumber = 0;
    accSampleSum = 0;

    attachInterrupt(acceleratorInterruptPin, risingAcceleratorPWMPulse, RISING);
    return;

  } else {
    attachInterrupt(acceleratorInterruptPin, risingAcceleratorPWMPulse, RISING);
    return;
  }
}

void risingAcceleratorPWMPulse() {
  acceleratorPreviousTime = micros();
  attachInterrupt(acceleratorInterruptPin, fallingAcceleratorPWMPulse, FALLING);
}

AcceleratorPedal::AcceleratorPedal(int pwmPinInput, int pwmPinOutput, int maximumPercent) {
  ACCELERATOR_PWM_PIN_INPUT = pwmPinInput;
  ACCELERATOR_PWM_PIN_OUTPUT = pwmPinOutput;
  pinMode(ACCELERATOR_PWM_PIN_INPUT, INPUT);
  pinMode(ACCELERATOR_PWM_PIN_OUTPUT, OUTPUT);

  acceleratorInterruptPin = digitalPinToInterrupt(ACCELERATOR_PWM_PIN_INPUT);
  attachInterrupt(acceleratorInterruptPin, risingAcceleratorPWMPulse, RISING);

  this->maximumPercent = maximumPercent;

  esc.attach(ACCELERATOR_PWM_PIN_OUTPUT);
  this->accelerate(0);
}

void AcceleratorPedal::accelerate(int percent) {
  // -1 (BRAKE) to 100 (FULL ACCELERATOR)
  acceleratorPercent = percent;

  int outputValue;

  if (percent < -20) {
    outputValue = RAW_BRAKE;
  } else {
    outputValue = map(acceleratorPercent, 0, 100, RAW_NO_ACCELERATOR, RAW_FULL_ACCELERATOR);
  }

  // Serial.println(outputValue);
  esc.write(outputValue);
}

int AcceleratorPedal::getAcceleratorPercent() {
  if (acceleratorIsManual) {
    acceleratorPercent = map(rawAcceleratorInputPWM, RAW_NO_ACCELERATOR, RAW_FULL_ACCELERATOR, 0, 100);
  } else {
    acceleratorPercent = 0;
  }

  return acceleratorPercent;
}