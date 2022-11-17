
#include "AcceleratorPedal.hpp"

// Might conflict with interrupt of steering reading, when pulse happens at the same time
void fallingAcceleratorPWMPulse() {
  int currentTime = micros();
  short int timeDifference = currentTime - acceleratorPreviousTime;

  rawAcceleratorInputPWM = timeDifference;

  if (rawAcceleratorInputPWM < 1460 || rawAcceleratorInputPWM > 1480) {
    acceleratorIsManual = true;
  } else {
    acceleratorIsManual = false;
  }

  attachInterrupt(acceleratorInterruptPin, risingAcceleratorPWMPulse, RISING);
}

void risingAcceleratorPWMPulse() {
  acceleratorPreviousTime = micros();
  attachInterrupt(acceleratorInterruptPin, fallingAcceleratorPWMPulse, FALLING);
}

AcceleratorPedal::AcceleratorPedal(int pwmPinInput, int pwmPinOutput) {
  ACCELERATOR_PWM_PIN_INPUT = pwmPinInput;
  ACCELERATOR_PWM_PIN_OUTPUT = pwmPinOutput;
  Serial.print("ACCELERATOR_PWM_PIN_INPUT: " + String(ACCELERATOR_PWM_PIN_INPUT) + "\t");
  Serial.print("AcceleratorPedal constructor called\n");
  pinMode(ACCELERATOR_PWM_PIN_INPUT, INPUT);
  pinMode(ACCELERATOR_PWM_PIN_OUTPUT, OUTPUT);

  acceleratorInterruptPin = digitalPinToInterrupt(ACCELERATOR_PWM_PIN_INPUT);
  attachInterrupt(acceleratorInterruptPin, risingAcceleratorPWMPulse, RISING);
}

void AcceleratorPedal::accelerate(int percent) {
  int outputValue;

  if (percent < 0) {
    outputValue = RAW_BRAKE;
  } else {
    outputValue = map(percent, 0, 100, RAW_NO_ACCELERATOR, RAW_FULL_ACCELERATOR);
  }

  analogWrite(acceleratorOutputPin, outputValue);
}