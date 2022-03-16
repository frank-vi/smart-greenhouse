#ifndef __SPEAKER_IMPL__
#define __SPEAKER_IMPL__

#include "Speaker.h"

class SpeakerImpl : public Speaker {
	public:
		SpeakerImpl(int pin);
    void play();
		void stop();

	private:
		int pin;
};

#endif
