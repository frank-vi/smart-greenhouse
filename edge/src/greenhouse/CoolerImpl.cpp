#include "Arduino.h"
#include "FanImpl.h"
#include "CoolerImpl.h"
#include "HumidifierImpl.h"

CoolerImpl::CoolerImpl(int pinFanIn, int pinFanOut, int pinHum) {
  this->fanIn = new FanImpl(pinFanIn);
  this->fanOut = new FanImpl(pinFanOut);
  this->hum = new HumidifierImpl(pinHum);
}

void CoolerImpl::cool() {
  this->fanIn->switchOn();
  this->fanOut->switchOn();
  this->hum->switchOn();
}

void CoolerImpl::noCool() {
  this->fanIn->switchOff();
  this->fanOut->switchOff();
  this->hum->switchOff();
}
