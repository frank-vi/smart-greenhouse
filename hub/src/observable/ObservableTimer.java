package observable;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import event.Event;
import event.Tick;
import observer.Observer;

public class ObservableTimer implements Timer  {

	private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
	private ScheduledFuture<?> tickHandle;
	private IObservable observable;
	private Runnable tickTask;
	private boolean isPeriodic;
	
	public ObservableTimer(){		
		observable = new Observable();
	    isPeriodic = false;
	    tickTask = () -> {
	    	Tick ev = new Tick(System.currentTimeMillis());
	    	observable.notifyEvent(ev);
	    };
	}
	
	/**
	 * Start generating tick event
	 * 
	 * @param period period in milliseconds
	 */
	public synchronized void start(long period){
		isPeriodic = true;
		tickHandle = scheduler.scheduleAtFixedRate(tickTask, 0, period, TimeUnit.MILLISECONDS);    
	}

	/**
	 * Generate a tick event after a number of milliseconds
	 * 
	 * @param delta
	 */
	public synchronized void scheduleTick(long deltat){
		tickHandle = scheduler.schedule(tickTask, deltat, TimeUnit.MILLISECONDS);
	}
	/**
	 * Stop generating tick event
	 * 
	 * @param period period in milliseconds
	 */
	public synchronized void stop(){
		if (tickHandle != null){
			tickHandle.cancel(false);
			tickHandle = null;
		}
	}
	
	public synchronized void restart(long time) {
		stop();
		if(isPeriodic) {
			start(time);
		} else {
			scheduleTick(time);
		}
	}
	
	public void addObserver(Observer obs){
		observable.addObserver(obs);
	}

	public void removeObserver(Observer obs){
		observable.removeObserver(obs);
	}

	@Override
	public void notifyEvent(Event ev) {
		observable.notifyEvent(ev);
	}
	
}
