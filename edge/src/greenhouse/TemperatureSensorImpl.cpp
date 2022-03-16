#include "Arduino.h"
#include "TemperatureSensorImpl.h"

TemperatureSensorImpl::TemperatureSensorImpl(int pin) {
  this->pin = pin;
  readTemp();
}

int TemperatureSensorImpl::readTemp() {
  int readV = analogRead(pin);
  long voltage = 5000L * long(readV);
  float millivolts = float(voltage) / 1024.0;
  return round(millivolts/10.0);
}
