package observable;

import java.util.Set;

import event.Event;
import observer.Observer;

import java.util.HashSet;

public class Observable implements IObservable {
	
	private Set<Observer> observers;
	
	protected Observable(){
		observers = new HashSet<Observer>();
	}
	
	public void notifyEvent(Event ev){
		synchronized (observers){
			for (Observer obs: observers){
				obs.notifyEvent(ev);
			}
		}
	}

	public void addObserver(Observer obs){
		synchronized (observers){
			observers.add(obs);
		}
	}

	public void removeObserver(Observer obs){
		synchronized (observers){
			observers.remove(obs);
		}
	}

}
