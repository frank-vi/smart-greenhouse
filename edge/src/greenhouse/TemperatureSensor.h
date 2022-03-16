#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

class TemperatureSensor {
public:
  virtual int readTemp() = 0;
};

#endif
