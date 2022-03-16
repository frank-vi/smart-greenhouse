package display;

import java.io.IOException;

import com.pi4j.component.lcd.LCD;

public interface Display extends LCD {

	void switchOnBackLight() throws IOException;

	void switchOffBackLight() throws IOException;

	void toggleBackLight() throws IOException;
	
}
