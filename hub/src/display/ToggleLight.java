package display;

import java.io.IOException;

public interface ToggleLight extends Light {
	void toggle() throws IOException;
}
