package event;

public class Tick implements Event {
	
	private long time;
	
	public Tick(long time ){
		this.time = time;
	}
	
	public long getTime(){
		return time;
	}
}
