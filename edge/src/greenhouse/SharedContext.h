#ifndef __SHARED_CONTEXT__
#define __SHARED_CONTEXT__

#include "Arduino.h"

class SharedContext {
public:
	bool isTankFull();
	void isTankFull(bool flag);
	static SharedContext* getInstance();
private:
	SharedContext();
	bool tankFull;
  static SharedContext* instance;
};

#endif
