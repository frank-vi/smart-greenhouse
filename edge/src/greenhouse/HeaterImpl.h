#ifndef __HEATER_IMPL__
#define __HEATER_IMPL__

#include "Heater.h"

class HeaterImpl : public Heater {
public:
  HeaterImpl(int pin);
  void heat();
  void noHeat();

private:
  int pin;
};

#endif
