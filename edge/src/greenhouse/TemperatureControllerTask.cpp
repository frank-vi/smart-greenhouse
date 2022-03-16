#include "Arduino.h"
#include "TemperatureControllerTask.h"

#define SET_TOLERANCE "tol"
#define SET_MIN_TEMPERATURE "mint"
#define SET_MAX_TEMPERATURE "maxt"

#define DEFAULT_TOLERANCE 0.3 //30%
#define DEFAULT_MIN_TEMPERATURE 20 //20°
#define DEFAULT_MAX_TEMPERATURE 30 //30°

TemperatureControllerTask::TemperatureControllerTask(MsgService* msgService, Heater* heater, Cooler* cooler,
    TemperatureSensor* temperatureSensor, ComunicationServiceTask* comService) {
  this->heater = heater;
  this->cooler = cooler;
  this->comService = comService;
  this->msgService = msgService;
  this->temperatureSensor = temperatureSensor;
  this->context = SharedContext::getInstance();
  this->comService->subscribe(SET_TOLERANCE, this);
  this->comService->subscribe(SET_MIN_TEMPERATURE, this);
  this->comService->subscribe(SET_MAX_TEMPERATURE, this);
}

void TemperatureControllerTask::init(unsigned long period) {
  Task::init(period);
  this->state = IDLE;
  this->prevTemperature = 0;
  this->tolerance = DEFAULT_TOLERANCE;
  this->minTemperature = DEFAULT_MIN_TEMPERATURE;
  this->maxTemperature = DEFAULT_MAX_TEMPERATURE;
  setAllTempRange();
  msgService->sendMsg(Msg("thermos", "off"));
}

void TemperatureControllerTask::updateTemperature(int currentTemperature) {
  if(currentTemperature != prevTemperature) {
    msgService->sendMsg(Msg("temper", String(currentTemperature)));
    prevTemperature = currentTemperature;
  }
}

void TemperatureControllerTask::tick() {
  int currentTemperature = temperatureSensor->readTemp();

  switch(state) {
    case IDLE: {
      if(currentTemperature < minTempTolerated) {
        heater->heat();
        msgService->sendMsg(Msg("thermos", "heating"));
        state = HEATING;
      } else if(currentTemperature > maxTempTolerated) {
        cooler->cool();
        msgService->sendMsg(Msg("thermos", "cooling"));
        state = COOLING;
      }
      break;
    }
    case HEATING: {
      if(currentTemperature > maxTempTolerated) {
        heater->noHeat();
        cooler->cool();
        msgService->sendMsg(Msg("thermos", "cooling"));
        state = COOLING;
      } else if(minMeanTemp < currentTemperature && currentTemperature < maxMeanTemp) {
        heater->noHeat();
        msgService->sendMsg(Msg("thermos", "off"));
        state = IDLE;
      }
      break;
    }
    case COOLING: {
      if(currentTemperature < minTempTolerated) {
        cooler->noCool();
        heater->heat();
        msgService->sendMsg(Msg("thermos", "heating"));
        state = HEATING;
      } else if(minMeanTemp < currentTemperature && currentTemperature < maxMeanTemp) {
        cooler->noCool();
        msgService->sendMsg(Msg("thermos", "off"));
        state = IDLE;
      }
      break;
    }
  }
  updateTemperature(currentTemperature);
}

void TemperatureControllerTask::onReceive(const String& action, const String& content) {
  if(action.equals(SET_MIN_TEMPERATURE)) {
    minTemperature = content.toFloat();
    setAllTempRange();
  } else if(action.equals(SET_MAX_TEMPERATURE)) {
    maxTemperature = content.toFloat();
    setAllTempRange();
  } else if(action.equals(SET_TOLERANCE)) {
    tolerance = content.toFloat();
    setAllTempRange();
  } else if(action.equals("update")) {
    if(state == HEATING) {
      msgService->sendMsg(Msg("thermos", "heating"));
    } else if(state == COOLING) {
      msgService->sendMsg(Msg("thermos", "cooling"));
    } else {
      msgService->sendMsg(Msg("thermos", "off"));
    }
    msgService->sendMsg(Msg("temper", String(prevTemperature)));
  }
}

void TemperatureControllerTask::setAllTempRange() {
  float tempRange = (maxTemperature - minTemperature);
  minTempTolerated = minTemperature - (tempRange * tolerance);
  maxTempTolerated = maxTemperature + (tempRange * tolerance);
  minMeanTemp = minTemperature + (tempRange * tolerance);
  maxMeanTemp = maxTemperature - (tempRange * tolerance);
}
