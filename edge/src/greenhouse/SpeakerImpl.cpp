#include "Arduino.h"
#include <NewTone.h>
#include "SpeakerImpl.h"

#define TONE_FREQUENCY 5000

SpeakerImpl::SpeakerImpl(int pin) {
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

void SpeakerImpl::play() {
	NewTone(pin, TONE_FREQUENCY);
}

void SpeakerImpl::stop() {
	noNewTone(pin);
}
