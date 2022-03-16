#ifndef __FAN_IMPL__
#define __FAN_IMPL__

#include "Fan.h"

class FanImpl : public Fan {
private:
  int pin;
  
public:
  FanImpl(int pin);
  void switchOn();
  void switchOff();
};

#endif
