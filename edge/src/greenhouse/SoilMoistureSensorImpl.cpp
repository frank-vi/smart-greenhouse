#include "Arduino.h"
#include "SoilMoistureSensorImpl.h"

SoilMoistureSensorImpl::SoilMoistureSensorImpl(int pin) {
  this->pin = pin;
}

int SoilMoistureSensorImpl::readSoilMoisture() {
  int voltage = analogRead(pin);
  return map(voltage, 0, 1023, 100, 0);
}
