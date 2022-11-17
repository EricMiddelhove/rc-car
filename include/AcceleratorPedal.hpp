#ifndef AcceleratorPedal_hpp
#define AcceleratorPedal_hpp

#include "Arduino.h"
void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

// TODO: Adjust Values
const short int RAW_FULL_ACCELERATOR = 2020;
const short int RAW_NO_ACCELERATOR = 1500;
const short int RAW_BRAKE = 980;

short int ACCELERATOR_PWM_PIN_INPUT;
short int ACCELERATOR_PWM_PIN_OUTPUT;
int acceleratorPreviousTime;
byte acceleratorInterruptPin;
byte rawAcceleratorInputPWM;

bool acceleratorIsManual;

byte acceleratorPercent;
byte manualPWMInput;

void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

class AcceleratorPedal {
 public:
  byte acceleratorOutputPin;
  AcceleratorPedal(int pwmPinInput, int pwmPinOutput);
  void accelerate(int percent);
};
#endif