#ifndef __HUMIDIFIER_IMPL__
#define __HUMIDIFIER_IMPL__

#include "Humidifier.h"

class HumidifierImpl : public Humidifier {
private:
  int pin;

public:
  HumidifierImpl(int pin);
  void switchOn();
  void switchOff();
};

#endif
