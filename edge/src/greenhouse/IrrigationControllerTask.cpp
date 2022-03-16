#include "ClockUtility.h"
#include "IrrigationControllerTask.h"

#define NUMBER_DETECTION 3
#define DEFAULT_HOT_END 54000 //ore: 15
#define DEFAULT_HOT_START 39600 //ore: 11
#define DEFAULT_MOISTURE_LEVEL 40 //40%

#define SET_END_HOT_TIME  "seht"
#define SET_MOISTURE_LEVEL  "sml"
#define SET_START_HOT_TIME  "ssht"

IrrigationControllerTask::IrrigationControllerTask(MsgService* msgService, Sprinkler* sprinkler,
    SoilMoistureSensor* soilMoistureSensor, ComunicationServiceTask* comService) {
  this->sprinkler = sprinkler;
  this->msgService = msgService;
  this->context = SharedContext::getInstance();
  this->soilMoistureSensor = soilMoistureSensor;
  this->comService = comService;
  this->comService->subscribe(SET_END_HOT_TIME, this);
  this->comService->subscribe(SET_START_HOT_TIME, this);
  this->comService->subscribe(SET_MOISTURE_LEVEL, this);
}

void IrrigationControllerTask::init(unsigned long period) {
  Task::init(period);
  this->state = PUMP_OFF;
  this->prevMoisture = 0;
  this->hotEndTime = DEFAULT_HOT_END;
  this->hotStartTime = DEFAULT_HOT_START;
  this->moistureLevel = DEFAULT_MOISTURE_LEVEL;
  msgService->sendMsg(Msg("irr", "off"));
  updateControlUnit(soilMoistureSensor->readSoilMoisture());
}

void IrrigationControllerTask::updateControlUnit(int currentMoisture) {
  if(currentMoisture != prevMoisture) {
    msgService->sendMsg(Msg("soil", String(currentMoisture)));
    prevMoisture = currentMoisture;
  }
}

void IrrigationControllerTask::tick() {
  int soilMoisture = soilMoistureSensor->readSoilMoisture();
  long timeAsSeconds = ClockUtility::hoursAndMinutesAsSeconds();

  switch (state) {
    case PUMP_OFF:
      if(soilMoisture < moistureLevel && context->isTankFull() &&
            (hotEndTime < timeAsSeconds || timeAsSeconds < hotStartTime)) {
        msgService->sendMsg(Msg("irr", "on"));
        sprinkler->water();
        state = PUMP_ON;
      }
      break;
    case PUMP_ON:
      if((hotStartTime < timeAsSeconds && timeAsSeconds < hotEndTime) ||
                  soilMoisture > moistureLevel || !context->isTankFull()) {
        msgService->sendMsg( Msg("irr", "off"));
        sprinkler->noWater();
        state = PUMP_OFF;
      }
      break;
  }
  updateControlUnit(soilMoisture);
}

void IrrigationControllerTask::onReceive(const String& action, const String& content) {
  if(action.equals(SET_MOISTURE_LEVEL)) {
    moistureLevel = content.toInt();
  } else if(action.equals(SET_START_HOT_TIME)) {
    hotStartTime = content.toInt();
  } else if(action.equals(SET_END_HOT_TIME)) {
    hotEndTime = content.toInt();
  } else if(action.equals("update")) {
    if(state == PUMP_ON) {
      msgService->sendMsg( Msg("irr", "on"));
    } else {
      msgService->sendMsg( Msg("irr", "off"));
    }
    msgService->sendMsg(Msg("soil", String(prevMoisture)));
  }
}
