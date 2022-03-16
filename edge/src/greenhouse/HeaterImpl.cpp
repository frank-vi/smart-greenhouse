#include "Arduino.h"
#include "HeaterImpl.h"

HeaterImpl::HeaterImpl(int pin) {
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void HeaterImpl::heat() {
  digitalWrite(pin, LOW);
}

void HeaterImpl::noHeat() {
  digitalWrite(pin, HIGH);
}
