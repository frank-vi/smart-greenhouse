#ifndef __CLOCK_CONTROLLER_TASK__
#define __CLOCK_CONTROLLER_TASK__

#include "Task.h"
#include "Clock.h"
#include "MsgService.h"
#include "SharedContext.h"
#include "BroadcastReceiver.h"
#include "ComunicationServiceTask.h"

class ClockControllerTask : public Task, public BroadcastReceiver {
public:
  ClockControllerTask(Clock* clock, MsgService* msgService, ComunicationServiceTask* comService);
  void init(unsigned long period);
  void tick();

  void onReceive(const String& action, const String& content);

private:
  int count;
  Clock* clock;
  bool isTriggered;
  MsgService* msgService;
  SharedContext* context;
  ComunicationServiceTask* comService;
  enum {CLOCK_NOT_WIRED, CLOCK_UPDATING, CLOCK_UPDATED} state;
};

#endif
