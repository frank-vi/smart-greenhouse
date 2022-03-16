package state;

import event.Event;
import observer.DisplayManager;

public interface FsmState {
	void entry();
	void exit();
	void processEvent(DisplayManager context, Event event);
}
