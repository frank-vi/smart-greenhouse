#ifndef __LAMP__
#define __LAMP__

#include "Light.h"

class Lamp : public Light {
private:
  int pin;
public:
  Lamp(int pin);
  void switchOn();
  void switchOff();
};

#endif
