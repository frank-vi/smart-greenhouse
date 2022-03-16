#ifndef __BROADCAST_RECEIVER__
#define __BROADCAST_RECEIVER__

#include "Arduino.h"

class BroadcastReceiver {
public:
  virtual void onReceive(const String& action, const String& content) = 0;
};

#endif
