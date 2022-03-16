package observable;

public interface Timer extends IObservable {
	
	public void start(long period);

	/**
	 * Generate a tick event after a number of milliseconds
	 * 
	 * @param delta
	 */
	public void scheduleTick(long deltat);
	
	/**
	 * Stop generating tick event
	 * 
	 * @param period period in milliseconds
	 */
	public void stop();
	
	public void restart(long time);
	
}
