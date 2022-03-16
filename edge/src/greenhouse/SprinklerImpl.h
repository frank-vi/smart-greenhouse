#ifndef __SPRINKLER_IMPL__
#define __SPRINKLER_IMPL__

#include "Sprinkler.h"

class SprinklerImpl : public Sprinkler {
public:
  SprinklerImpl(int pin);
  void water();
  void noWater();
  
private:
  int pin;
};

#endif
