#include "Esp32_TB6612.hpp"
#include <Arduino.h>

// TB6612FNG has maximum PWM switching frequency of 100kHz.
#define DEFAULT_LEDC_FREQ 5000

Motor::Motor(int IN1pin, int IN2pin, int PWMpin, int channel, int resolution)
{
  IN1 = IN1pin;
  IN2 = IN2pin;
  PWM = PWMpin;
  _channel = channel;
  _resolution = resolution;

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(STBY, OUTPUT);

  ledcAttachPin(PWM, _channel);
  ledcSetup(_channel, DEFAULT_LEDC_FREQ, _resolution);
}

void Motor::drive(int speed) {
  if(speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if(speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  ledcWrite(_channel, abs(speed));
}
