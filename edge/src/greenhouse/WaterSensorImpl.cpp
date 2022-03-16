#include "Arduino.h"
#include "WaterSensorImpl.h"

WaterSensorImpl::WaterSensorImpl(int pin) {
  this->pin = pin;
}

int WaterSensorImpl::readWaterLevel() {
  int voltage = analogRead(pin);
  return map(voltage, 0, 470, 0, 100);
}
