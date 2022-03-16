package observable;

import event.Event;
import event.RepositoryUpdated;
import observer.Observer;

public class ObservableRepository implements Repository {

	private static final String NOT_SET = "---";
	private volatile long[] light;
	private volatile String clock, water, temperature, soilMoisture;
	private volatile String irrigation, thermostat, illumination;
	private IObservable observable;
	
	private ObservableRepository() {
		this.clock = NOT_SET;
		this.light = new long[]{0,0,0};
		this.water = NOT_SET;
		this.temperature = NOT_SET;
		this.soilMoisture = NOT_SET;
		this.irrigation = NOT_SET;
		this.thermostat = NOT_SET;
		this.illumination = NOT_SET;
		this.observable = new Observable();
	}

	private static class SingletonHelper{
        private static final Repository INSTANCE = new ObservableRepository();
    }
    
    public static Repository getInstance(){
        return SingletonHelper.INSTANCE;
    }
	
	@Override
	public String getClockInfo() {
		return this.clock;
	}

	@Override
	public long[] getLightInfo() {
		return this.light;
	}
	
	@Override
	public String getIrrigationInfo() {
		return this.irrigation;
	}

	@Override
	public String getThermostatInfo() {
		return this.thermostat;
	}

	@Override
	public String getWaterInTankInfo() {
		return this.water;
	}

	@Override
	public String getTemperatureInfo() {
		return this.temperature;
	}

	@Override
	public String getSoilMoistureInfo() {
		return this.soilMoisture;
	}
	
	@Override
	public String getIlluminationInfo() {
		return this.illumination;
	}

	@Override
	public synchronized void setClockInfo(String info) {
		this.clock = info;
		observable.notifyEvent(new RepositoryUpdated());
	}

	@Override
	public synchronized void setLightInfo(long[] time) {
		this.light = time;
		observable.notifyEvent(new RepositoryUpdated());
	}
	
	@Override
	public synchronized void setIrrigationInfo(String info) {
		this.irrigation = info;
		observable.notifyEvent(new RepositoryUpdated());
	}

	@Override
	public synchronized void setThermostatInfo(String info) {
		this.thermostat = info;
		observable.notifyEvent(new RepositoryUpdated());
	}

	@Override
	public synchronized void setWaterInTankInfo(String info) {
		this.water = info;
		observable.notifyEvent(new RepositoryUpdated());
	}

	@Override
	public synchronized void setTemperatureInfo(String info) {
		this.temperature = info;
		observable.notifyEvent(new RepositoryUpdated());
	}

	@Override
	public synchronized void setSoilMoistureInfo(String info) {
		this.soilMoisture = info;
		observable.notifyEvent(new RepositoryUpdated());
	}

	@Override
	public synchronized void setIlluminationInfo(String info) {
		this.illumination = info;
		observable.notifyEvent(new RepositoryUpdated());
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
