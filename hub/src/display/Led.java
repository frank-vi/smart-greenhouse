package display;

import java.io.IOException;

import com.pi4j.io.gpio.*;

import main.Config;

public class Led implements Light {
	
	@SuppressWarnings("unused")
	private int pinNum;
	private GpioPinDigitalOutput pin;
	
	public Led(int pinNum){

		this.pinNum = pinNum;
		try {
		    GpioController gpio = GpioFactory.getInstance();
		    pin = gpio.provisionDigitalOutputPin(Config.pinMap[pinNum]);		    
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public synchronized void switchOn() throws IOException {
		pin.high();
	}

	@Override
	public synchronized void switchOff() throws IOException {
		pin.low();
	}
	
}
