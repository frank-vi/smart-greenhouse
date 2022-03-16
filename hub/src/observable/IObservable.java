package observable;

import event.Event;
import observer.Observer;

public interface IObservable {

	public void notifyEvent(Event ev);
	
	public void addObserver(Observer obs);

	public void removeObserver(Observer obs);
	
}
