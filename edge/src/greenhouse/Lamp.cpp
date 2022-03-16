#include "Lamp.h"
#include <Arduino.h>

Lamp::Lamp(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Lamp::switchOn() {
  digitalWrite(pin, LOW);
}

void Lamp::switchOff() {
  digitalWrite(pin, HIGH);
}
