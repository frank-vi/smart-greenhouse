package messaging_system;

import java.util.Collection;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import org.eclipse.paho.client.mqttv3.IMqttAsyncClient;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MqttCommChannel implements CommChannel, MqttCallback {
	
	private static final int MAX_MSG = 100;
	private Collection<String> topics;
	private BlockingQueue<IMsg> queue;
	private IMqttAsyncClient clientDevice;
	
	public MqttCommChannel(String brokerUrl, Collection<String> topics) throws MqttException {
		super();
		this.topics = topics;
		queue = new ArrayBlockingQueue<>(MAX_MSG);
		clientDevice = new MqttAsyncClient(brokerUrl,
				MqttAsyncClient.generateClientId(), new MemoryPersistence());	
		clientDevice.setCallback(this);
	}

	@Override
	public void connect() throws Exception {
		if(!clientDevice.isConnected()) {
			MqttConnectOptions connOpts = new MqttConnectOptions();
			connOpts.setCleanSession(false);
			connOpts.setAutomaticReconnect(true);
			IMqttToken tok = clientDevice.connect(connOpts);
			tok.waitForCompletion();
			
			for(String topic : topics) {
				clientDevice.subscribe(topic, 1);
			}
		}
	}
	
	@Override
	public synchronized void close() throws Exception {
		if(clientDevice.isConnected()) {
			for(String topic : topics) {
				clientDevice.unsubscribe(topic);
			}
			clientDevice.disconnect();
		}
	}

	@Override
	public synchronized void sendMsg(IMsg message) {
		if(clientDevice.isConnected()) {
			try {
				clientDevice.publish(message.getTopic(), new MqttMessage(message.getContent().getBytes()));
			} catch (MqttException e) {
				e.printStackTrace();
			}
		}	
	}
	
	@Override
	public synchronized IMsg receiveMsg() throws InterruptedException {
		return queue.take();
	}
	
	@Override
	public synchronized boolean isMsgAvailable() {
		return !queue.isEmpty();
	}

	@Override
	public void connectionLost(Throwable cause) {}

	@Override
	public void deliveryComplete(IMqttDeliveryToken token) {}

	@Override
	public void messageArrived(String topic, MqttMessage message) throws Exception {
		IMsg msg = new Msg(topic, message.toString());
		queue.put(msg);
	}

}
