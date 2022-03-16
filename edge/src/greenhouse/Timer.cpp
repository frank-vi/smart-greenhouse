#include "Timer.h"
#include "Arduino.h"

#include <FlexiTimer2.h>

volatile bool timerFlag;

void doTick(){
  timerFlag = true;
}

/* period in ms */
void Timer::setupPeriod(int period){
  FlexiTimer2::set(period, doTick);
  FlexiTimer2::start();
}

void Timer::waitForNextTick(){
  /* wait for timer signal */
  while (!timerFlag){}
  timerFlag = false;
  
}
