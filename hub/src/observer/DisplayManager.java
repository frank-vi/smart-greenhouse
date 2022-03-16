package observer;

import java.util.ArrayList;
import java.util.List;

import display.Display;
import event.Event;
import messaging_system.CommChannel;
import messaging_system.Msg;
import observable.Button;
import observable.ObservableRepository;
import observable.ObservableTimer;
import observable.Timer;
import state.Alarm;
import state.AllInfo;
import state.FsmState;
import state.IlluminationInfo;
import state.IrrigationInfo;
import state.Off;
import state.ThermostatInfo;

public class DisplayManager extends BasicEventLoopController {
	
	private CommChannel intranet;
	private FsmState currentState;
	private final List<FsmState> states;
	public static enum FSMState{OFF, ALARM, ALL_INFO, THERMOSTAT_INFO, IRRIGATION_INFO, ILLUMINATION_INFO};
	
	public DisplayManager(CommChannel intranet, CommChannel internet, Display display, Button backButton,
			Button homeButton, Button nextButton) {
		this.intranet = intranet;
		Timer timer = new ObservableTimer();
		states = new ArrayList<>(6);
		states.add(new Off(display, homeButton));
		states.add(new Alarm(intranet, internet, timer, display, homeButton));
		states.add(new AllInfo(display, timer, homeButton, backButton, nextButton));
		states.add(new ThermostatInfo(display, timer, homeButton, backButton, nextButton));
		states.add(new IrrigationInfo(display, timer, homeButton, backButton, nextButton));
		states.add(new IlluminationInfo(display, timer, homeButton, backButton, nextButton));
		setInitialState(FSMState.OFF);
		startObserving(timer);
		startObserving(backButton);
		startObserving(homeButton);
		startObserving(nextButton);
		startObserving(ObservableRepository.getInstance());
	}
	
	private void setInitialState(FSMState fsmState) {
		currentState = states.get(fsmState.ordinal());
        currentState.entry();
		intranet.sendMsg(new Msg("update"));
	}

	public void setState(FSMState fsmState) {
		currentState.exit();
        currentState = states.get(fsmState.ordinal());
		currentState.entry();
    }

	@Override
    protected void processEvent(Event event) {
    	currentState.processEvent(this, event);
    }
}