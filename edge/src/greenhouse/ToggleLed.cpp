#include "Led.h"
#include "ToggleLed.h"

ToggleLed::ToggleLed(int pin) {
  this->isOn = false;
  this->light = new Led(pin);
}

void ToggleLed::switchOn() {
  light->switchOn();
}

void ToggleLed::switchOff() {
  light->switchOff();
}

void ToggleLed::toggle() {
  if(isOn) {
    isOn = false;
    light->switchOff();
  } else {
    isOn = true;
    light->switchOn();
  }
}
