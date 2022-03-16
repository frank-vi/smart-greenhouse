#ifndef __TIMER__
#define __TIMER__

class Timer {
    
public:  
  /* period in ms */
  void setupPeriod(int period);  
  void waitForNextTick();

};


#endif

