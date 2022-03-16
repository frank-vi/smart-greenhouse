#include "ClockUtility.h"
#include "IlluminatingLampTask.h"

#define SET_LIGHT_TIME  "slt"
#define SET_SUNSET_TIME "ssst"
#define SET_SUNRISE_TIME  "ssrt"
#define SET_LIGHT_INTENSITY "sli"

#define DEFAULT_SUNSET_TIME 64800 //ore: 18
#define DEFAULT_SUNRISE_TIME 28800 //ore: 8
#define DEFAULT_LIGHTING_TIME_REQUIRED 18000 //5h
#define DEFAULT_LIGHT_INTENSITY_REQUIRED 80 //80%

IlluminatingLampTask::IlluminatingLampTask(MsgService* msgService, Light* light,
    LightSensor* lightSensor, ComunicationServiceTask* comService) {
  this->light = light;
  this->comService = comService;
  this->msgService = msgService;
  this->lightSensor = lightSensor;
  this->comService->subscribe(SET_LIGHT_TIME, this);
  this->comService->subscribe(SET_SUNSET_TIME, this);
  this->comService->subscribe(SET_SUNRISE_TIME, this);
  this->comService->subscribe(SET_LIGHT_INTENSITY, this);
}

void IlluminatingLampTask::init(unsigned long period){
  Task::init(period);
  this->state = IDLE;
  this->prevLightAmount = 0;
  this->lightingTimeDetected = 0;
  this->sunsetTime = DEFAULT_SUNSET_TIME;
  this->sunriseTime = DEFAULT_SUNRISE_TIME;
  this->lightingTimeRequired = DEFAULT_LIGHTING_TIME_REQUIRED;
  this->lightIntensityRequired = DEFAULT_LIGHT_INTENSITY_REQUIRED;
  msgService->sendMsg(Msg("ill", "off"));
  msgService->sendMsg(Msg("lightq", String(lightingTimeDetected)));
}

void IlluminatingLampTask::updateControlUnit(long lightAmount) {
  if(lightAmount != prevLightAmount) {
    msgService->sendMsg(Msg("lightq", String(lightAmount)));
    prevLightAmount = lightAmount;
  }
}

void IlluminatingLampTask::tick() {
  switch(this->state) {
    case IDLE: {
      long timeAsSeconds = ClockUtility::hoursAndMinutesAsSeconds();
      if(sunriseTime < timeAsSeconds && timeAsSeconds < sunsetTime) {
        this->lightingTimeDetected = 0;
        this->state = SENSING;
        msgService->sendMsg(Msg("ill", "sense"));
      } else if(lightingTimeDetected < lightingTimeRequired) {
        this->light->switchOn();
        msgService->sendMsg(Msg("ill", "on"));
        this->state = ILLUMINATING;
      }
      break;
    }
    case SENSING: {
      long timeAsSeconds = ClockUtility::hoursAndMinutesAsSeconds();
      if(this->lightingTimeDetected >= this->lightingTimeRequired) {
        msgService->sendMsg(Msg("ill", "off"));
        this->state = IDLE;
      } else if(sunsetTime < timeAsSeconds || timeAsSeconds < sunriseTime) {
        this->light->switchOn();
        msgService->sendMsg(Msg("ill", "on"));
        this->state = ILLUMINATING;
      } else if(lightSensor->getLightIntensity() >= this->lightIntensityRequired) {
        this->lightingTimeDetected++;
      }
      break;
    }
    case ILLUMINATING: {
      long timeAsSeconds = ClockUtility::hoursAndMinutesAsSeconds();
      if(sunriseTime < timeAsSeconds && timeAsSeconds < sunsetTime) {
        this->lightingTimeDetected = 0;
        this->light->switchOff();
        msgService->sendMsg(Msg("ill", "sense"));
        this->state = SENSING;
      } else if(this->lightingTimeDetected >= this->lightingTimeRequired) {
        this->light->switchOff();
        msgService->sendMsg(Msg("ill", "off"));
        this->state = IDLE;
      } else if(lightSensor->getLightIntensity() >= this->lightIntensityRequired) {
        this->lightingTimeDetected++;
      }
      break;
    }
  }
  updateControlUnit(lightingTimeDetected);
}

void IlluminatingLampTask::onReceive(const String& action, const String& content) {
  if(action.equals(SET_SUNRISE_TIME)) {
    this->sunriseTime = ClockUtility::getTime(content);
  } else if(action.equals(SET_SUNSET_TIME)) {
    this->sunsetTime = ClockUtility::getTime(content);
  } else if(action.equals(SET_LIGHT_TIME)) {
    this->lightingTimeRequired = content.toInt();
  } else if(action.equals(SET_LIGHT_INTENSITY)) {
    this->lightIntensityRequired = content.toInt();
  } else if(action.equals("update")) {
    if(state == ILLUMINATING) {
      msgService->sendMsg(Msg("ill", "on"));
    } else if(state == SENSING) {
      msgService->sendMsg(Msg("ill", "sense"));
    } else {
      msgService->sendMsg(Msg("ill", "off"));
    }
    msgService->sendMsg(Msg("lightq", String(prevLightAmount)));
  }
}
