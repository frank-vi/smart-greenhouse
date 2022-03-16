#ifndef __FAN__
#define __FAN__

class Fan {
public:
  virtual void switchOn() = 0;
  virtual void switchOff() = 0;
};

#endif
