package observable;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;

import event.ButtonPressed;
import event.Event;
import main.Config;
import observer.Observer;

public class ObservableButton implements Button {

	private GpioPinDigitalInput pin;
	private IObservable observable;
	
	public ObservableButton(int pinNum){
		super();
		try {
		    GpioController gpio = GpioFactory.getInstance();
		    pin = gpio.provisionDigitalInputPin(Config.pinMap[pinNum],PinPullResistance.PULL_DOWN);
		} catch (Exception e) {
			e.printStackTrace();
		}
		observable = new Observable();
		pin.addListener(new ButtonListener(this));
	}
	
	@Override
	public synchronized boolean isPressed() {
		return pin.isHigh();
	}
	
	public void addObserver(Observer obs){
		observable.addObserver(obs);
	}

	public void removeObserver(Observer obs){
		observable.removeObserver(obs);
	}
	
	class ButtonListener implements GpioPinListenerDigital {		
		Button button;
		
		public ButtonListener(Button button){
			this.button = button;
		}

		public void handleGpioPinDigitalStateChangeEvent(GpioPinDigitalStateChangeEvent event)  {
        	if (event.getState().isHigh()){
        		Event ev = new ButtonPressed(button);
            	notifyEvent(ev);
            }
        }
	}

	@Override
	public void notifyEvent(Event ev) {
		observable.notifyEvent(ev);
	}

}
