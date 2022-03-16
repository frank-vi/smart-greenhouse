#ifndef __IRRIGATION_CONTROLLER_TASK__
#define __IRRIGATION_CONTROLLER_TASK__

#include "Task.h"
#include "Sprinkler.h"
#include "MsgService.h"
#include "SharedContext.h"
#include "BroadcastReceiver.h"
#include "SoilMoistureSensor.h"
#include "ComunicationServiceTask.h"

class IrrigationControllerTask : public Task, public BroadcastReceiver {
public:
  IrrigationControllerTask(MsgService* msgService, Sprinkler* sprinkler,
    SoilMoistureSensor* soilMoistureSensor, ComunicationServiceTask* comService);
  void init(unsigned long period);
  void tick();

  void updateControlUnit(int currentMoisture);
  void onReceive(const String& action, const String& content);
private:
  Sprinkler* sprinkler;
  MsgService* msgService;
  SharedContext* context;
  long hotEndTime, hotStartTime;
  enum {PUMP_OFF, PUMP_ON} state;
  int moistureLevel, prevMoisture;
  ComunicationServiceTask* comService;
  SoilMoistureSensor* soilMoistureSensor;
};

#endif
