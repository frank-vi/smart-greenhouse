package state;

import com.pi4j.component.lcd.LCDTextAlignment;

import display.Display;
import event.ButtonPressed;
import event.Event;
import observable.Button;
import observable.Timer;
import observer.DisplayManager;

public class ThermostatInfo extends ShowInfo {

	private final String TAG = "ThermostatInfo";
	private final Button backButton, nextButton;
	
	public ThermostatInfo(Display display, Timer timer, Button homeButton,
			Button backButton, Button nextButton) {
		super(timer, display, homeButton);
		this.backButton = backButton;
		this.nextButton = nextButton;
	}
	
	@Override
	public void entry() {
		System.out.println("[" + TAG + "]: entry");
		super.entry();
	}
	
	@Override
	public void exit() {
		super.exit();
		System.out.println("[" + TAG + "]: exit");
	}

	@Override
	protected void updateInfo() {
		String firstRow = "Temperature " + (repository.getTemperatureInfo().length() < 2 ? " " + repository.getTemperatureInfo() : repository.getTemperatureInfo()) + " C";
		String secondRow = "<Thermostat " + repository.getThermostatInfo().substring(0,3) + ">";
		display.writeln(LCD_ROW_1, firstRow, LCDTextAlignment.ALIGN_LEFT);
	    display.write(LCD_ROW_2, secondRow, LCDTextAlignment.ALIGN_LEFT);
	}
	
	@Override
	public void processEvent(DisplayManager context, Event event) {
		if(event instanceof ButtonPressed) {
			Button button = ((ButtonPressed)event).getSourceButton();
			if(button.equals(backButton)) {
				log("ButtonPressed:back", "go to AllInfo");
				context.setState(DisplayManager.FSMState.ALL_INFO);
			} else if(button.equals(nextButton)) {
				log("ButtonPressed:next", "go to IrrigationInfo");
				context.setState(DisplayManager.FSMState.IRRIGATION_INFO);
			}
		}
		super.processEvent(context, event);
	}

}
