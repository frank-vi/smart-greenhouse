#include "Arduino.h"
#include "SharedContext.h"

SharedContext* SharedContext::instance = NULL;

SharedContext::SharedContext() {
  this->tankFull = true;
}

SharedContext* SharedContext::getInstance() {
  if(!instance) {
    instance = new SharedContext();
  }
  return instance;
}

bool SharedContext::isTankFull() {
  return this->tankFull;
}

void SharedContext::isTankFull(bool full) {
  this->tankFull = full;
}
