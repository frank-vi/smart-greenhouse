#ifndef __TANK_MONITORING_TASK__
#define __TANK_MONITORING_TASK__

#include "Task.h"
#include "Speaker.h"
#include "MsgService.h"
#include "ToggleLight.h"
#include "WaterSensor.h"
#include "SharedContext.h"
#include "BroadcastReceiver.h"
#include "ComunicationServiceTask.h"

class TankMonitoringTask : public Task, public BroadcastReceiver {
public:
  TankMonitoringTask(MsgService* msgService, WaterSensor* waterSensor, ToggleLight* light,
    Speaker* speaker, ComunicationServiceTask* comService);
  void init(unsigned long period);
  void tick();

  void updateControlUnit(int currentWaterLevel);
  void onReceive(const String& action, const String& content);
private:
  bool silence;
  Speaker* speaker;
  ToggleLight* light;
  MsgService* msgService;
  SharedContext* context;
  WaterSensor* waterSensor;
  int waterLevel, prevWaterLevel;
  ComunicationServiceTask* comService;
  enum {WATER, NO_WATER_ALARM, ALARM_SILENT} state;
};

#endif
