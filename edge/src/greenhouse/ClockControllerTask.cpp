#include "ClockControllerTask.h"

#define SET_CLOCK_TIME "sct"

ClockControllerTask::ClockControllerTask(Clock* clock, MsgService* msgService, ComunicationServiceTask* comService) {
  this->clock = clock;
  this->context = SharedContext::getInstance();
  this->msgService = msgService;
  this->comService = comService;
  this->comService->subscribe(SET_CLOCK_TIME, this);
}

void ClockControllerTask::init(unsigned long period) {
  Task::init(period);
  count = 0;
  isTriggered = false;
  state = CLOCK_UPDATING;
  msgService->sendMsg(Msg("sync"));
}

void ClockControllerTask::tick() {
  switch(state) {
    case CLOCK_NOT_WIRED: {
      clock->getTime();
      if(clock->isWired()) {
        msgService->sendMsg(Msg("sync"));
        count = 0;
        state = CLOCK_UPDATING;
      }
      break;
    }
    case CLOCK_UPDATING: {
      clock->getTime();
      if(!clock->isWired()) {
        state = CLOCK_NOT_WIRED;
      } else if(isTriggered) {
        isTriggered = false;
        count = 0;
        state = CLOCK_UPDATED;
      } else if(count < 60) {
        count++;
      } else {
        count = 0;
        msgService->sendMsg(Msg("sync"));
      }
      break;
    }
    case CLOCK_UPDATED: {
      clock->getTime();
      if(!clock->isWired()) {
        state = CLOCK_NOT_WIRED;
      } else if(count < 1800) {
        count++;
      } else {
        count = 0;
        msgService->sendMsg(Msg("sync"));
        state = CLOCK_UPDATING;
      }
      break;
    }
  }
}

void ClockControllerTask::onReceive(const String& action, const String& content) {
  if(action.equals(SET_CLOCK_TIME)) {
    int hourIndex = content.indexOf(':');
    int hour = content.substring(0, hourIndex).toInt();
    int minute = content.substring(hourIndex+1).toInt();
    clock->setTime(hour, minute);
    isTriggered = true;
  }
}
