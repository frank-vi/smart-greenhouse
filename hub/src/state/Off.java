package state;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import display.Display;
import event.AlarmEvent;
import event.ButtonPressed;
import event.Event;
import observable.Button;
import observer.DisplayManager;

public class Off implements FsmState {

	private static final String TAG = "Off";
	
	private final Display display;
	private final Button homeButton;
	private final SimpleDateFormat hourFormatter;

	public Off(Display display, Button homeButton) {
		super();
		this.display = display;
		this.homeButton = homeButton;
		hourFormatter = new SimpleDateFormat("HH:mm");
	}
	
	@Override
	public void entry() {
		System.out.println("[" + TAG + "]: entry");
		try {
			display.switchOffBackLight();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void exit() {
		try {
			display.switchOnBackLight();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("[" + TAG + "]: exit");
	}

	@Override
	public void processEvent(DisplayManager context, Event event) {
		if (event instanceof AlarmEvent){
			log("MsgEvent:alarm", "go to Alarm");
			context.setState(DisplayManager.FSMState.ALARM);
    	} else if (event instanceof ButtonPressed) {
    		Button button = ((ButtonPressed) event).getSourceButton();
    		if(button.equals(homeButton)) {
		        log("ButtonPressed:home", "go to AllInfo");
    			context.setState(DisplayManager.FSMState.ALL_INFO);
    		}
	    }
	}

	private void log(String event, String transition) {
		System.out.println(hourFormatter.format(new Date()) + " [" + event + "]: " + transition);
	}

}
