#ifndef AcceleratorPedal_hpp
#define AcceleratorPedal_hpp

#include "Arduino.h"
#include "Servo.h"

void fallingAcceleratorPWMPulse();
void risingAcceleratorPWMPulse();

// TODO: Adjust Values
const int8_t ACC_INPUT_SAMPLE_SIZE = 10;
int RAW_FULL_ACCELERATOR = 2020;
int RAW_NO_ACCELERATOR = 1500;
int RAW_BRAKE = 980;

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
  AcceleratorPedal(int pwmPinInput, int pwmPinOutput, int maximumPercent);
  void accelerate(int percent);
  int getAcceleratorPercent();

 private:
  Servo esc;
  int maximumPercent;
  int acceleratorPercent;
};
#endif