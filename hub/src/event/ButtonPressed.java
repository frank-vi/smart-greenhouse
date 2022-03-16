package event;

import observable.Button;

public class ButtonPressed implements Event {
	private Button source;
	
	public ButtonPressed(Button source){
		this.source = source;
	}
	
	public Button getSourceButton(){
		return source;
	}
}
