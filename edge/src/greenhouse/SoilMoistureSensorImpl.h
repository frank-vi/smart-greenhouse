#ifndef __SOIL_MOISTURE_SENSOR_IMPL__
#define __SOIL_MOISTURE_SENSOR_IMPL__

#include "SoilMoistureSensor.h"

class SoilMoistureSensorImpl : public SoilMoistureSensor {
public:
  SoilMoistureSensorImpl(int pin);
  int readSoilMoisture();

private:
  int pin;
};

#endif
