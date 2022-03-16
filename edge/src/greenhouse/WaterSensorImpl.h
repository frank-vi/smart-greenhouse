#ifndef __WATER_SENSOR_IMPL__
#define __WATER_SENSOR_IMPL__

#include "WaterSensor.h"

class WaterSensorImpl : public WaterSensor {
public:
  WaterSensorImpl(int pin);
  int readWaterLevel();

private:
  int pin;
};

#endif
