package state;

import java.text.SimpleDateFormat;
import java.util.Date;

import com.pi4j.component.lcd.LCDTextAlignment;

import display.Display;
import event.ButtonPressed;
import event.Event;
import observable.Button;
import observable.Timer;
import observer.DisplayManager;

public class AllInfo extends ShowInfo {

	private final String TAG = "AllInfo";
	private final Button backButton, nextButton;
	private final SimpleDateFormat hourFormatter;
	
	public AllInfo(Display display, Timer timer, Button homeButton, Button backButton, Button nextButton) {
		super(timer, display, homeButton);
		this.backButton = backButton;
		this.nextButton = nextButton;
		hourFormatter = new SimpleDateFormat("HH:mm");
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
		String irrigationInfo = "";
		if(repository.getIrrigationInfo().equals("on")) {
			irrigationInfo  = "Irr on";
		} else if(repository.getIrrigationInfo().equals("off")){
			irrigationInfo = "Ir off";
		} else {
			irrigationInfo = "Irr --";
		}
		
		String thermostatInfo = "Th ";
		if(repository.getThermostatInfo().equals("off")) {
			thermostatInfo += " off";
		} else if(repository.getThermostatInfo().equals("cooling") || repository.getThermostatInfo().equals("heating")){
			thermostatInfo += repository.getThermostatInfo().substring(0, 4);
		} else {
			thermostatInfo += "----";
		}
		
		String illuminationInfo = "";
		if(repository.getIlluminationInfo().equals("on")) {
			illuminationInfo = "Illum on";
		} else if(repository.getIlluminationInfo().equals("off")){
			illuminationInfo = "Ill  off";
		} else if(repository.getIlluminationInfo().equals("sense")){
			illuminationInfo = "Il sense";
		} else {
			illuminationInfo = "Illum --";
		}
		/*
		String textOnFirstRow = hourFormatter.format(new Date()) +
				" " + (repository.getThermostatInfo().length() > 3 ? repository.getThermostatInfo().substring(0, 3) : repository.getThermostatInfo().toString()) +
				" " + (repository.getIrrigationInfo().length() > 3 ? repository.getIrrigationInfo().substring(0, 3) : repository.getIrrigationInfo().toString()) +
				" " + (repository.getIlluminationInfo().length() > 3 ? repository.getIlluminationInfo().substring(0, 3) : repository.getIlluminationInfo().toString());*/
		display.writeln(LCD_ROW_1, irrigationInfo + "   " + thermostatInfo, LCDTextAlignment.ALIGN_LEFT);
		display.writeln(LCD_ROW_2, "<" + hourFormatter.format(new Date()) + " " + illuminationInfo + ">", LCDTextAlignment.ALIGN_LEFT);
	}
	
	@Override
	public void processEvent(DisplayManager context, Event event) {
		if(event instanceof ButtonPressed) {
			Button button = ((ButtonPressed)event).getSourceButton();
			if(button.equals(backButton)) {
				log("ButtonPressed:back", "go to IlluminationInfo");
				context.setState(DisplayManager.FSMState.ILLUMINATION_INFO);
			} else if(button.equals(nextButton)) {
				log("ButtonPressed:next", "go to ThermostatInfo");
				context.setState(DisplayManager.FSMState.THERMOSTAT_INFO);
			}
		}
		super.processEvent(context, event);
	}

}
