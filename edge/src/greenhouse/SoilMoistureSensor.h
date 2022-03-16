#ifndef __SOIL_MOISTURE_SENSOR__
#define __SOIL_MOISTURE_SENSOR__

class SoilMoistureSensor {
public:
  virtual int readSoilMoisture() = 0;
};

#endif
