package display;

import java.io.IOException;

public interface Light {
	void switchOn() throws IOException;
	void switchOff() throws IOException;
}
