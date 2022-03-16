package messaging_system;

public class Msg implements IMsg {

	private final String topic, content;
	
	public Msg(String topic) {
		this(topic, "");
	}
	
	public Msg(String topic, String content) {
		super();
		this.topic = topic;
		this.content = content;
	}

	@Override
	public String getTopic() {
		return topic;
	}

	@Override
	public String getContent() {
		return content;
	}

}
