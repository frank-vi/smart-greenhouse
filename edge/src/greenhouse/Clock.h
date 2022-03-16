#ifndef __CLOCK__
#define __CLOCK__

#include <TimeLib.h>

class Clock {
public:
  virtual bool isWired() = 0;
  virtual time_t getTime() = 0;
  virtual void setTime(time_t time) = 0;
  virtual void setTime(int hour, int minute) = 0;
};

#endif
