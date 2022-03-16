package state;

import java.text.SimpleDateFormat;
import java.util.Date;

import display.Display;
import event.AlarmEvent;
import event.ButtonPressed;
import event.Event;
import event.RepositoryUpdated;
import event.Tick;
import observable.Button;
import observable.ObservableRepository;
import observable.Repository;
import observable.Timer;
import observer.DisplayManager;

public abstract class ShowInfo implements FsmState {

	protected static final int LCD_ROW_1 = 0;
	protected static final int LCD_ROW_2 = 1;
	
	private final Timer timer;
	private final Button homeButton;
	protected final Display display;
	protected final Repository repository;
	private final SimpleDateFormat hourFormatter;
	
	public ShowInfo(Timer timer, Display display, Button homeButton) {
		this.timer = timer;
		this.display = display;
		this.homeButton = homeButton;
		hourFormatter = new SimpleDateFormat("HH:mm");
		repository = ObservableRepository.getInstance();
	}
	
	@Override
	public void entry() {
		timer.scheduleTick(60000);
		updateInfo();
	}

	@Override
	public void exit() {
		timer.stop();
		display.clear();
	}
	
	protected abstract void updateInfo();

	@Override
	public void processEvent(DisplayManager context, Event event) {
		if (event instanceof AlarmEvent){
			log("MsgEvent:alarm", "go to Alarm");
			context.setState(DisplayManager.FSMState.ALARM);
		} else if(event instanceof RepositoryUpdated) {
			log("MsgEvent:update", "");
			updateInfo();
		} else if (event instanceof ButtonPressed) {
    		ButtonPressed event1 = (ButtonPressed) event;
    		if(event1.getSourceButton().equals(homeButton)) {
    			log("ButtonPressed:home", "go to Off");
    			context.setState(DisplayManager.FSMState.OFF);
    		}
    	} else if (event instanceof Tick) {
    		log("Tick", "go to Off");
    		context.setState(DisplayManager.FSMState.OFF);
    	}
	}
	
	protected void log(String event, String transition) {
		System.out.println(hourFormatter.format(new Date()) + " ["+ event +"]: " + transition);
	}

}
