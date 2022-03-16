package state;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.pi4j.component.lcd.LCDTextAlignment;

import display.Display;
import event.AlarmDisabled;
import event.ButtonPressed;
import event.Event;
import event.Tick;
import messaging_system.CommChannel;
import messaging_system.IMsg;
import messaging_system.Msg;
import observable.Button;
import observable.Timer;
import observer.DisplayManager;

public class Alarm implements FsmState {

	private static final String TAG = "Alarm";
	private static final long BLINK_PERIOD = 100;
	private static final int LCD_ROW_1 = 0;
	private static final int LCD_ROW_2 = 1;
	
	private final Timer timer;
	private final Display display;
	private final Button homeButton;
	private final CommChannel intranet, internet;
	private final SimpleDateFormat hourFormatter;

	public Alarm(CommChannel intranet, CommChannel internet, Timer timer,
			Display display, Button homeButton) {
		super();
		this.timer = timer;
		this.display = display;
		this.intranet = intranet;
		this.internet = internet;
		this.homeButton = homeButton;
		hourFormatter = new SimpleDateFormat("HH:mm");
	}

	@Override
	public void entry() {
		System.out.println("[" + TAG + "]: entry");
        timer.start(BLINK_PERIOD);
		display.writeln(LCD_ROW_1, "Alarm", LCDTextAlignment.ALIGN_CENTER);
		display.writeln(LCD_ROW_2, "missing water!", LCDTextAlignment.ALIGN_CENTER);
	}

	@Override
	public void exit() {
		timer.stop();
		System.out.println("[" + TAG + "]: entry");
	}

	@Override
	public void processEvent(DisplayManager context, Event event) {
		if (event instanceof ButtonPressed) {
    		ButtonPressed event1 = (ButtonPressed) event;
    		if(event1.getSourceButton().equals(homeButton)) {
				IMsg msg = new Msg("Alarm", "silent");
    			intranet.sendMsg(msg);
    			internet.sendMsg(msg);
    			
    			log("ButtonPressed:home", "go to Off");
    			context.setState(DisplayManager.FSMState.OFF);
    		}
    	} else if (event instanceof Tick) {
    		try {
				display.toggleBackLight();
				display.writeln(LCD_ROW_1, "Alarm", LCDTextAlignment.ALIGN_CENTER);
				display.writeln(LCD_ROW_2, "missing water!", LCDTextAlignment.ALIGN_CENTER);
			} catch (IOException e) {
				e.printStackTrace();
			}
    		log("Tick", "");
    	} else if (event instanceof AlarmDisabled) {
			log("Msgevent:alarm", "go to Off");
			context.setState(DisplayManager.FSMState.OFF);
    	}
	}

	private void log(String event, String transition) {
		System.out.println(hourFormatter.format(new Date()) + " [" + event + "]:" + transition);
	}

}
