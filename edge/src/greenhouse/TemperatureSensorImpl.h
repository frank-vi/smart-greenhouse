#ifndef __TEMPERATURE_SENSOR_IMPL__
#define __TEMPERATURE_SENSOR_IMPL__

#include "TemperatureSensor.h"

class TemperatureSensorImpl : public TemperatureSensor {
public:
  TemperatureSensorImpl(int pin);
  int readTemp();

private:
  int pin;
};

#endif
