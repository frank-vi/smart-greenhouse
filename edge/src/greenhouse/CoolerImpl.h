#ifndef __COOLER_IMPL__
#define __COOLER_IMPL__

#include "Fan.h"
#include "Cooler.h"
#include "Humidifier.h"

class CoolerImpl : public Cooler {
public:
  CoolerImpl(int pinFanIn, int pinFanOut, int pinHum);
  void cool();
  void noCool();

private:
  Fan* fanIn;
  Fan* fanOut;
  Humidifier* hum;
};

#endif
