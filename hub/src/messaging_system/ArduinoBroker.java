package messaging_system;

import java.text.SimpleDateFormat;
import java.util.Date;

import event.AlarmDisabled;
import event.AlarmEvent;
import observable.ObservableRepository;
import observable.Repository;
import observer.DisplayManager;

public class ArduinoBroker extends Thread {

	private static final String TOPIC_HOUR = "sct";
	
	private final Repository repository;
	private final DisplayManager displayManager;
	private final SimpleDateFormat hourFormatter;
	private final CommChannel inputChannel, outputChannel;
	
	public ArduinoBroker(CommChannel inputChannel, CommChannel outputChannel, DisplayManager displayManager) {
		super();
		this.inputChannel = inputChannel;
		this.outputChannel = outputChannel;
		this.displayManager = displayManager;
		this.repository = ObservableRepository.getInstance();
		hourFormatter = new SimpleDateFormat("HH:mm");
	}

	@Override
	public void run(){
		while (true){
			try {
				IMsg msg = inputChannel.receiveMsg();
				
				switch(msg.getTopic()) {
					case "sync":
						inputChannel.sendMsg(new Msg(TOPIC_HOUR, hourFormatter.format(new Date())));
						break;
					case "ill":
						repository.setIlluminationInfo(msg.getContent());
						outputChannel.sendMsg(msg);
						break;
					case "lightq":
						long secondsLight = Long.parseLong(msg.getContent());
						long hours = secondsLight / 3600;
						long minutes = (secondsLight % 3600) / 60;
						long seconds = secondsLight % 60;
						long[] time = new long[]{hours, minutes, seconds};
						repository.setLightInfo(time);
						outputChannel.sendMsg(msg);
						break;
					case "irr":
						repository.setIrrigationInfo(msg.getContent());
						outputChannel.sendMsg(msg);
						break;
					case "soil":
						repository.setSoilMoistureInfo(msg.getContent());
						outputChannel.sendMsg(msg);
						break;
					case "temper":
						repository.setTemperatureInfo(msg.getContent());
						outputChannel.sendMsg(msg);
						break;
					case "thermos":
						repository.setThermostatInfo(msg.getContent());
						outputChannel.sendMsg(msg);
						break;					
					case "water":
						repository.setWaterInTankInfo(msg.getContent());
						outputChannel.sendMsg(msg);
						break;
					case "talarm":
						if(msg.getContent().compareTo("on") == 0) {
							displayManager.notifyEvent(new AlarmEvent());
						} else {
							displayManager.notifyEvent(new AlarmDisabled());
							outputChannel.sendMsg(msg);
						}
						outputChannel.sendMsg(msg);
						break;
					default:
						break;
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
}
