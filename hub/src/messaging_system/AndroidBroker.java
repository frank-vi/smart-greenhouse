package messaging_system;

import event.AlarmDisabled;
import event.Event;
import observer.DisplayManager;

public class AndroidBroker extends Thread {

	private final DisplayManager displayManager;
	private final CommChannel inputChannel, outputChannel;
	
	public AndroidBroker(CommChannel inputChannel, CommChannel outputChannel, DisplayManager displayManager) {
		super();
		this.inputChannel = inputChannel;
		this.outputChannel = outputChannel;
		this.displayManager = displayManager;
	}

	@Override
	public void run(){
		while (true){
			try {
				IMsg msg = inputChannel.receiveMsg();
				
				if(msg.getTopic().compareTo("sillarm") == 0) {
					Event event = new AlarmDisabled();
					displayManager.notifyEvent(event);
				}
				
				outputChannel.sendMsg(msg);
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
}
