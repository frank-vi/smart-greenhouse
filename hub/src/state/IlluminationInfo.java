package state;

import com.pi4j.component.lcd.LCDTextAlignment;

import display.Display;
import event.ButtonPressed;
import event.Event;
import observable.Button;
import observable.Timer;
import observer.DisplayManager;

public class IlluminationInfo extends ShowInfo {

	private final String TAG = "IlluminationInfo";
	private final Button backButton, nextButton;
	
	public IlluminationInfo(Display display, Timer timer, Button homeButton,
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
		String firstRow = "Light  ";
		long[] time = repository.getLightInfo();
		
		if(Long.toString(time[0]).length() < 2) {
			firstRow += " " + time[0] + "h";
		} else {
			firstRow += time[0] + "h";
		}
		
		if(Long.toString(time[1]).length() < 2) {
			firstRow += " " + time[1] + "'";
		} else {
			firstRow += time[1] + "'";
		}
		
		if(Long.toString(time[2]).length() < 2) {
			firstRow += " " + time[2] + "\"";
		} else {
			firstRow += time[2] + "\"";
		}
		
		String secondRow = "";
		if(repository.getIlluminationInfo().equals("on")) {
			secondRow = "< Illuminat on >";
		} else if(repository.getIlluminationInfo().equals("off")){
			secondRow = "<Illuminat  off>";
		} else if(repository.getIlluminationInfo().equals("sense")){
			secondRow = "<Illumin  sense>";
		} else {
			secondRow = "<Illuminat  --->";
		}
		
		display.writeln(LCD_ROW_1, firstRow, LCDTextAlignment.ALIGN_LEFT);
		display.writeln(LCD_ROW_2, secondRow, LCDTextAlignment.ALIGN_LEFT);
	}
	
	@Override
	public void processEvent(DisplayManager context, Event event) {
		if(event instanceof ButtonPressed) {
			Button button = ((ButtonPressed)event).getSourceButton();
			if(button.equals(backButton)) {
				log("ButtonPressed:back", "go to IrrigationInfo");
				context.setState(DisplayManager.FSMState.IRRIGATION_INFO);
			} else if(button.equals(nextButton)) {
				log("ButtonPressed:next", "go to AllInfo");
				context.setState(DisplayManager.FSMState.ALL_INFO);
			}
		}
		super.processEvent(context, event);
	}

}
