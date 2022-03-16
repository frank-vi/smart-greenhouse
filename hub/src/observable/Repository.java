package observable;

public interface Repository extends IObservable {

	public enum Info {WATER, TEMPERATURE, LIGHT, SOIL_MOISTURE, ILLUMINATION};

	public String getClockInfo();
	
	public long[] getLightInfo();
	
	public String getIrrigationInfo();

	public String getThermostatInfo();
	
	public String getWaterInTankInfo();
	
	public String getTemperatureInfo();
	
	public String getSoilMoistureInfo();
	
	public String getIlluminationInfo();

	public void setClockInfo(String info);

	public void setLightInfo(long[] time);

	public void setIrrigationInfo(String info);

	public void setThermostatInfo(String info);

	public void setWaterInTankInfo(String info);
	
	public void setTemperatureInfo(String info);
	
	public void setSoilMoistureInfo(String info);

	public void setIlluminationInfo(String info);

}
