#include "FanImpl.h"
#include <Arduino.h>

FanImpl::FanImpl(int pin) {
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void FanImpl::switchOn() {
  digitalWrite(pin, HIGH);
}

void FanImpl::switchOff() {
  digitalWrite(pin, LOW);
}
