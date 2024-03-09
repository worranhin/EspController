#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include <Arduino.h>

enum Pins {
  stepPin1 = GPIO_NUM_4,
  dirPin1 = GPIO_NUM_5,
  stepPin2 = GPIO_NUM_6,
  dirPin2 = GPIO_NUM_7,
  stepPin3 = GPIO_NUM_15,
  dirPin3 = GPIO_NUM_16,
  stepPin4 = GPIO_NUM_10,
  dirPin4 = GPIO_NUM_11
};

#endif