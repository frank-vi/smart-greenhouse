#include "Arduino.h"
#include "LightSensorImpl.h"

#define V_IN 5
#define LEVELS 1024
#define RESISTANCE 10f

LightSensorImpl::LightSensorImpl(int pin) {
  this->pin = pin;
}

int LightSensorImpl::getLightIntensity() {
  int intensity = analogRead(pin);
  return map(intensity, 0, 1023, 0, 100);
}
