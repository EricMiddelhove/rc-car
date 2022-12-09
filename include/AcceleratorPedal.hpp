#ifndef AcceleratorPedal_hpp
#define AcceleratorPedal_hpp

#include "Arduino.h"
void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

// TODO: Adjust Values
const int8_t ACC_INPUT_SAMPLE_SIZE = 10;
const short RAW_FULL_ACCELERATOR = 2020;
const short RAW_NO_ACCELERATOR = 1500;
const short RAW_BRAKE = 980;

short ACCELERATOR_PWM_PIN_INPUT;
short ACCELERATOR_PWM_PIN_OUTPUT;
unsigned long acceleratorPreviousTime;
byte acceleratorInterruptPin;
int rawAcceleratorInputPWM;

bool acceleratorIsManual;

byte manualPWMInput;

void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

class AcceleratorPedal {
 public:
  byte acceleratorOutputPin;
  AcceleratorPedal(int pwmPinInput, int pwmPinOutput);
  void accelerate(int percent);
  int getAcceleratorPercent();

 private:
  int8_t acceleratorPercent;
};
#endif