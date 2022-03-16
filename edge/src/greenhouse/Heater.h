#ifndef __HEATER__
#define __HEATER__

class Heater {
public:
  virtual void heat() = 0;
  virtual void noHeat() = 0;
};

#endif
