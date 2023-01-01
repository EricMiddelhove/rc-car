#include <Arduino.h>

byte PWM_PIN = 3;
byte PWM_OUT_PIN = 10;

int pwm_value;

void setup() {
  pinMode(PWM_PIN, INPUT);
  pinMode(PWM_OUT_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  Serial.println(pwm_value);
  analogWrite(PWM_OUT_PIN, pwm_value);
  delay(100);
}