#ifndef AcceleratorPedal_hpp
#define AcceleratorPedal_hpp

#include "Arduino.h"
void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

// TODO: Adjust Values
const int RAW_FULL_ACCELERATOR = 2020;
const int RAW_NO_ACCELERATOR = 1500;
const int RAW_BRAKE = 980;

int ACCELERATOR_PWM_PIN_INPUT;
int ACCELERATOR_PWM_PIN_OUTPUT;
int acceleratorPreviousTime;
int acceleratorInterruptPin;
int rawAcceleratorInputPWM;

bool acceleratorIsManual;

int acceleratorPercent;
int manualPWMInput;

void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

class AcceleratorPedal {
 public:
  byte acceleratorOutputPin;
  AcceleratorPedal(int pwmPinInput, int pwmPinOutput);
  void accelerate(int percent);
};
#endif