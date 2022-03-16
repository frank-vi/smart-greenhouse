#ifndef __ILLUMINATING_LAMP_TASK__
#define __ILLUMINATING_LAMP_TASK__

#include "Task.h"
#include "Light.h"
#include "MsgService.h"
#include "LightSensor.h"
#include "BroadcastReceiver.h"
#include "ComunicationServiceTask.h"

class IlluminatingLampTask : public Task, public BroadcastReceiver {
public:
  IlluminatingLampTask(MsgService* msgService, Light* light, LightSensor* lightSensor, ComunicationServiceTask* comService);
  void init(unsigned long period);
  void tick();

  void updateControlUnit(long lightAmount);
  void onReceive(const String& action, const String& content);

private:
  Light* light;
  MsgService* msgService;
  LightSensor* lightSensor;
  int lightIntensityRequired;
  ComunicationServiceTask* comService;
  enum {IDLE, SENSING, ILLUMINATING} state;
  long sunsetTime, sunriseTime, lightingTimeDetected, lightingTimeRequired, prevLightAmount;
};

#endif
