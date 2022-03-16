#ifndef __TASK__
#define __TASK__

#include "Arduino.h"

class Task {

  protected:
    unsigned long myPeriod;
    unsigned long timeElapsed;

  public:
    virtual void init(unsigned long period) {
      myPeriod = period;
      timeElapsed = 0;
    }

    virtual void tick() = 0;

    int getPeriod() {
      return myPeriod;
    }

    bool updateAndCheckTime(int basePeriod) {
      timeElapsed += basePeriod;
      if (timeElapsed >= myPeriod) {
        timeElapsed = 0;
        return true;
      } else {
        return false;
      }
    }
};

#endif
