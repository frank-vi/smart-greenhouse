#ifndef __TEMPERATURE_CONTROLLER_TASK__
#define  __TEMPERATURE_CONTROLLER_TASK__

#include "Task.h"
#include "Heater.h"
#include "Cooler.h"
#include "MsgService.h"
#include "SharedContext.h"
#include "BroadcastReceiver.h"
#include "TemperatureSensor.h"
#include "ComunicationServiceTask.h"

class TemperatureControllerTask : public Task, public BroadcastReceiver {
public:
  TemperatureControllerTask(MsgService* msgService, Heater* heater, Cooler* cooler,
    TemperatureSensor* temperatureSensor, ComunicationServiceTask* comService);
  void init(unsigned long period);
  void tick();

  void setAllTempRange();
  void updateTemperature(int currentTemperature);
  void onReceive(const String& action, const String& content);

private:
  Heater* heater;
  Cooler* cooler;
  float tolerance;
  MsgService* msgService;
  SharedContext* context;
  ComunicationServiceTask* comService;
  TemperatureSensor* temperatureSensor;
  enum {IDLE, HEATING, COOLING} state;
  int minTemperature, maxTemperature, minTempTolerated, maxTempTolerated, minMeanTemp, maxMeanTemp, prevTemperature;
};

#endif
