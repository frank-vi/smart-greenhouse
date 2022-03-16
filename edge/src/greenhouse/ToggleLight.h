#ifndef __TOGGLE_LIGHT__
#define __TOGGLE_LIGHT__

#include "Light.h"

class ToggleLight : public Light {
public:
  virtual void toggle() = 0;
};

#endif
