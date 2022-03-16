package display;

import java.io.IOException;

public class ToggleLed implements ToggleLight {

	private Light led;
	private Boolean isOn;
	
	public ToggleLed(int pinNum) {
		this.led = new Led(pinNum);
		this.isOn = false;
	}

	@Override
	public synchronized void toggle() throws IOException {
		if(isOn) {
			led.switchOff();
		} else {
			led.switchOn();
		}
	}

	@Override
	public synchronized void switchOn() throws IOException {
		led.switchOn();
	}

	@Override
	public synchronized void switchOff() throws IOException {
		led.switchOff();
	}

}
