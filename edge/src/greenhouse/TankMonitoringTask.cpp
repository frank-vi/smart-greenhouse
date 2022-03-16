#include "TankMonitoringTask.h"

#define UPDATE "update"
#define SET_ALARM "sillarm"
#define DEFAULT_WATER_LEVEL 40 //40%

TankMonitoringTask::TankMonitoringTask(MsgService* msgService, WaterSensor* waterSensor,
    ToggleLight* light, Speaker* speaker, ComunicationServiceTask* comService) {
  this->light = light;
  this->speaker = speaker;
  this->comService = comService;
  this->msgService = msgService;
  this->waterSensor = waterSensor;
  this->context = SharedContext::getInstance();
  this->comService->subscribe(SET_ALARM, this);
  this->comService->subscribe(UPDATE, this);
}

void TankMonitoringTask::init(unsigned long period) {
  Task::init(period);
  this->state = WATER;
  this->silence = false;
  light->switchOn();
  context->isTankFull(true);
  this->waterLevel = DEFAULT_WATER_LEVEL;
  updateControlUnit(waterSensor->readWaterLevel());
  msgService->sendMsg(Msg("talarm", "off"));
}

void TankMonitoringTask::updateControlUnit(int currentWaterLevel) {
  if(currentWaterLevel != prevWaterLevel) {
    msgService->sendMsg(Msg("water", String(currentWaterLevel)));
    prevWaterLevel = currentWaterLevel;
  }
}

void TankMonitoringTask::tick() {
  int water = waterSensor->readWaterLevel();

  switch(state) {
    case WATER:
      if(water < waterLevel) {
        light->switchOff();
        speaker->play();
        context->isTankFull(false);
        msgService->sendMsg(Msg("talarm", "on"));
        state = NO_WATER_ALARM;
      }
      break;
    case NO_WATER_ALARM:
      if(water > waterLevel) {
        light->switchOn();
        speaker->stop();
        silence = false;
        context->isTankFull(true);
        msgService->sendMsg(Msg("talarm", "off"));
        state = WATER;
      } else if(silence) {
        speaker->stop();
        silence = false;
        state = ALARM_SILENT;
      } else {
        light->toggle();
      }
      break;
    case ALARM_SILENT:
      if(water > waterLevel) {
        light->switchOn();
        context->isTankFull(true);
        msgService->sendMsg(Msg("talarm", "off"));
        state = WATER;
      } else {
        light->toggle();
      }
      break;
  }
  updateControlUnit(water);
}

void TankMonitoringTask::onReceive(const String& action, const String& content) {
  if(action.equals(SET_ALARM)) {
    this->silence = true;
  } else if(action.equals(UPDATE)) {
    if(state == WATER || state == ALARM_SILENT) {
      msgService->sendMsg(Msg("talarm", "on"));
    } else {
      msgService->sendMsg(Msg("talarm", "off"));
    }
    msgService->sendMsg(Msg("water", String(prevWaterLevel)));
  }
}
