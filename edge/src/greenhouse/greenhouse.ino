#include <Arduino.h>
#include <TimeLib.h>

#include "Led.h"
#include "Lamp.h"
#include "Light.h"
#include "Clock.h"
#include "config.h"
#include "Heater.h"
#include "Cooler.h"
#include "Speaker.h"
#include "Sprinkler.h"
#include "ToggleLed.h"
#include "ClockImpl.h"
#include "Scheduler.h"
#include "MsgService.h"
#include "HeaterImpl.h"
#include "CoolerImpl.h"
#include "SpeakerImpl.h"
#include "ToggleLight.h"
#include "LightSensor.h"
#include "WaterSensor.h"
#include "SprinklerImpl.h"
#include "LightSensorImpl.h"
#include "WaterSensorImpl.h"
#include "TemperatureSensor.h"
#include "SoilMoistureSensor.h"
#include "TankMonitoringTask.h"
#include "ClockControllerTask.h"
#include "IlluminatingLampTask.h"
#include "TemperatureSensorImpl.h"
#include "SoilMoistureSensorImpl.h"
#include "ComunicationServiceTask.h"
#include "IrrigationControllerTask.h"
#include "TemperatureControllerTask.h"

#define MAX_TASKS 10

Scheduler sched(MAX_TASKS);
Clock* clock = new ClockImpl();

void setup() {
  MsgService* msgService = new MsgService();
  msgService->init();

  ComunicationServiceTask* comService = new ComunicationServiceTask(msgService);
  comService->init(100);

  ClockControllerTask* clockControllerTask = new ClockControllerTask(clock, msgService, comService);
  clockControllerTask->init(1000);

  setSyncProvider(syncTime);

  Light* light = new Lamp(LIGHT_PIN);
  LightSensor* lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
  IlluminatingLampTask* illuminatingLampTask = new IlluminatingLampTask(msgService, light, lightSensor, comService);
  illuminatingLampTask->init(5000);

  Heater* heater = new HeaterImpl(HEATER_PIN);
  Cooler* cooler = new CoolerImpl(FAN_IN_PIN, FAN_OUT_PIN, HUMIDIFIER_PIN);
  TemperatureSensor* temperatureSensor = new TemperatureSensorImpl(TEMPERATURE_SENSOR_PIN);
  TemperatureControllerTask* temperatureControllerTask =
    new TemperatureControllerTask(msgService, heater, cooler, temperatureSensor, comService);
  temperatureControllerTask->init(10000);

  Speaker* speaker = new SpeakerImpl(SPEAKER_PIN);
  ToggleLight* tankLed = new ToggleLed(TANK_LED_PIN);
  WaterSensor* waterSensor = new WaterSensorImpl(WATER_SENSOR_PIN);
  TankMonitoringTask* tankMonitoringTask =
    new TankMonitoringTask(msgService, waterSensor, tankLed, speaker, comService);
  tankMonitoringTask->init(500);

  Sprinkler* sprinkler = new SprinklerImpl(SPRINKLER_PIN);
  SoilMoistureSensor* soilMoistureSensor = new SoilMoistureSensorImpl(SOIL_MOISTURE_SENSOR_PIN);
  IrrigationControllerTask* irrigationControllerTask =
    new IrrigationControllerTask(msgService, sprinkler, soilMoistureSensor, comService);
  irrigationControllerTask->init(8000);

  sched.init(50);
  sched.addTask(comService);
  sched.addTask(clockControllerTask);
  sched.addTask(illuminatingLampTask);
  sched.addTask(temperatureControllerTask);
  sched.addTask(tankMonitoringTask);
  sched.addTask(irrigationControllerTask);
}

void loop() {
	sched.schedule();
}

time_t syncTime() {
    return clock->getTime();
}
