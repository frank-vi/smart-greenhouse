#ifndef __TOGGLE_LED__
#define __TOGGLE_LED__

#include "Light.h"
#include "ToggleLight.h"

class ToggleLed : public ToggleLight {
public:
  ToggleLed(int pin);
  void switchOn();
  void switchOff();
  void toggle();
private:
  bool isOn;
  Light* light;
};

#endif
