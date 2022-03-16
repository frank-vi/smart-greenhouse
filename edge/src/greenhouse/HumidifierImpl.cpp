#include "HumidifierImpl.h"
#include <Arduino.h>

HumidifierImpl::HumidifierImpl(int pin) {
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void HumidifierImpl::switchOn() {
  digitalWrite(pin, LOW);
}

void HumidifierImpl::switchOff() {
  digitalWrite(pin, HIGH);
}
