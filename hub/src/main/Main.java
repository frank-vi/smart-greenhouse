package main;

import java.util.HashSet;
import java.util.Set;

import display.Display;
import display.LcdDisplay;
import messaging_system.AndroidBroker;
import messaging_system.ArduinoBroker;
import messaging_system.CommChannel;
import messaging_system.MqttCommChannel;
import messaging_system.SerialCommChannel;
import observable.Button;
import observable.ObservableButton;
import observer.DisplayManager;

public class Main {
    public static void main(String args[]) throws Exception {
		Set<String> topics = new HashSet<>();
		topics.add("ssst"); //SetSunSetTime
		topics.add("mint"); //MinTemperature
    	topics.add("maxt"); //MaxTemperature
    	topics.add("ssrt"); //SetSunRiseTime
    	topics.add("seht"); //SetEndHotTime
    	topics.add("ssht"); //SetStartHotTime
    	topics.add("sillarm"); //SiLent_aLarm
    	topics.add("sli"); //SetLightIntensity
    	topics.add("sml"); //SetMoistureLevel
		
		Button backButton = new ObservableButton(3);
		Button homeButton = new ObservableButton(2);
		Button nextButton = new ObservableButton(0);
		Display screen = new LcdDisplay(2, 16, 11, 10, 6, 5, 4, 1, 7);
		
		CommChannel intranet = new SerialCommChannel(args[0], 9600);
    	CommChannel internet = new MqttCommChannel("tcp://test.mosquitto.org:1883", topics);
    
    	internet.connect();
		intranet.connect();
		
		DisplayManager hfsm = new DisplayManager(intranet, internet, screen, backButton, homeButton, nextButton);
    	ArduinoBroker arduinoBroker = new ArduinoBroker(intranet, internet, hfsm);
    	AndroidBroker androidBroker = new AndroidBroker(internet, intranet, hfsm);

    	hfsm.start();
    	arduinoBroker.start();
    	androidBroker.start();    	
    }
}