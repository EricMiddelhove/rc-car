#ifndef AcceleratorPedal_hpp
#define AcceleratorPedal_hpp

#include "Arduino.h"

void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

// TODO: Adjust Values
const int RAW_FULL_ACCELERATOR = 1836;
const int RAW_NO_ACCELERATOR = 1108;
const int RAW_NEUTRAL = 1470;

int PWM_PIN;
int previousTime;
int interruptPin;
int rawAcceleratorInputPWM;

bool acceleratorIsManual;

int acceleratorPercent;
int manualPWMInput;

class AcceleratorPedal {
 public:
  byte acceleratorOutputPin;
  AcceleratorPedal(int pwmPin);
  void accelerate(int percent);
};

#endif