package event;

import messaging_system.IMsg;

public class MsgEvent implements Event {
	
	private IMsg msg;

	public MsgEvent(IMsg msg){
		this.msg = msg;
	}
	
	public IMsg getMsg(){
		return msg;
	}
}
