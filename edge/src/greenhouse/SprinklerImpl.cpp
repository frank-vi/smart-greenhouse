#include "Arduino.h"
#include "SprinklerImpl.h"

SprinklerImpl::SprinklerImpl(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void SprinklerImpl::water() {
  digitalWrite(pin, LOW);
}

void SprinklerImpl::noWater() {
  digitalWrite(pin, HIGH);
}
