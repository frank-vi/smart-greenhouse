#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__

class LightSensor {
public:
  virtual int getLightIntensity() = 0;
};

#endif
