package display;

import java.io.IOException;

import com.pi4j.component.lcd.impl.GpioLcdDisplay;

import main.Config;

public class LcdDisplay extends GpioLcdDisplay implements Display {
	
	private ToggleLight backLight;
	
	public LcdDisplay(int rows, int columns, int vo, int rs, int strobe, int data1, int data2, int data3, int data4) {
		super(rows, columns, Config.pinMap[rs], Config.pinMap[strobe], Config.pinMap[data1],
				Config.pinMap[data2], Config.pinMap[data3], Config.pinMap[data4]);
		backLight = new ToggleLed(vo);
	}
	
	public LcdDisplay(int rows, int columns, int vo, int rs, int strobe, int data1, int data2, int data3, int data4, int data5, int data6, int data7, int data8) {
		super(rows, columns, Config.pinMap[rs], Config.pinMap[strobe],
				Config.pinMap[data1], Config.pinMap[data2], Config.pinMap[data3], Config.pinMap[data4],
				Config.pinMap[data5], Config.pinMap[data6], Config.pinMap[data7], Config.pinMap[data8]);
		backLight = new ToggleLed(vo);
	}
	
	@Override
	public void switchOnBackLight() throws IOException {
		this.backLight.switchOn();
	}
	
	@Override
	public void switchOffBackLight() throws IOException {
		this.backLight.switchOff();
	}
	
	@Override
	public void toggleBackLight() throws IOException {
		this.backLight.toggle();
	}
	
}