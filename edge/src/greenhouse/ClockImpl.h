#ifndef __CLOCK_IMPL__
#define __CLOCK_IMPL__

#include "Clock.h"

class ClockImpl : public Clock {
public:
  bool isWired();
  time_t getTime();
  void setTime(time_t time);
  void setTime(int hour, int minute);
};

#endif
