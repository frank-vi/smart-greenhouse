package state;

import com.pi4j.component.lcd.LCDTextAlignment;

import display.Display;
import event.ButtonPressed;
import event.Event;
import observable.Button;
import observable.Timer;
import observer.DisplayManager;


public class IrrigationInfo extends ShowInfo {
	
	private final String TAG = "IrrigationInfo";
	private final Button backButton, nextButton;
	
	public IrrigationInfo(Display display, Timer timer, Button homeButton,
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
		String firstInfo = "Mois";
		if(repository.getSoilMoistureInfo().length() == 1) {
			firstInfo += "  " + repository.getSoilMoistureInfo() + "%";
		} else if(repository.getSoilMoistureInfo().length() == 2) {
			firstInfo += " " + repository.getSoilMoistureInfo() + "%";
		} else if(repository.getSoilMoistureInfo().length() == 3){
			firstInfo += repository.getSoilMoistureInfo() + "%";
		} else {
			firstInfo += " ---";
		}
		
		String secondInfo = "Wat";
		if(repository.getWaterInTankInfo().length() == 1) {
			secondInfo += "  " + repository.getWaterInTankInfo() + "%";
		} else if(repository.getWaterInTankInfo().length() == 2) {
			secondInfo += " " + repository.getWaterInTankInfo() + "%";
		} else if(repository.getWaterInTankInfo().length() == 3){
			secondInfo += repository.getWaterInTankInfo() + "%";
		} else {
			secondInfo += " ---";
		}
		
	    String secondRow = "<Irrigation " + (repository.getIrrigationInfo().length() < 3 ? repository.getIrrigationInfo() + " " : repository.getIrrigationInfo()) + ">";
	    display.writeln(LCD_ROW_1, firstInfo + " " + secondInfo, LCDTextAlignment.ALIGN_LEFT);
	    display.writeln(LCD_ROW_2, secondRow, LCDTextAlignment.ALIGN_CENTER);
	}
	
	@Override
	public void processEvent(DisplayManager context, Event event) {
		if(event instanceof ButtonPressed) {
			Button button = ((ButtonPressed)event).getSourceButton();
			if(button.equals(backButton)) {
				log("ButtonPressed:back", "go to ThermostatInfo");
				context.setState(DisplayManager.FSMState.THERMOSTAT_INFO);
			} else if(button.equals(nextButton)) {
				log("ButtonPressed:next", "go to IlluminationInfo");
				context.setState(DisplayManager.FSMState.ILLUMINATION_INFO);
			}
		}
		super.processEvent(context, event);
	}

}
