package messaging_system;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

/**
 * Comm channel implementation based on serial port.
 * 
 * @author aricci, francesco.vignola
 *
 */
public class SerialCommChannel implements CommChannel, SerialPortEventListener {	
	
	private static final String APP_NAME = "Smart Greenhouse";
	private static final int TIME_OUT = 2000;
	private static final int MAX_MSG = 100;
	private final String port;
	private final int rate;
	
	private BlockingQueue<IMsg> queue;
	private SerialPort serialPort;
	private BufferedReader input;
	private OutputStream output;
	
	public SerialCommChannel(String port, int rate) {
		super();
		this.port = port;
		this.rate = rate;
		queue = new ArrayBlockingQueue<>(MAX_MSG);
	}
	
	@Override
	public void connect() throws Exception {
		if (serialPort == null) {
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(port);
			serialPort = (SerialPort) portId.open(APP_NAME, TIME_OUT);

			serialPort.setSerialPortParams(rate,
					SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);

			input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
			output = serialPort.getOutputStream();

			serialPort.addEventListener(this);
			serialPort.notifyOnDataAvailable(true);
		}
	}
	
	@Override
	public synchronized void close() {
		if (serialPort != null) {
			serialPort.removeEventListener();
			serialPort.close();
		}
	}

	@Override
	public void sendMsg(IMsg message) {
		if (serialPort == null) {
			String msg = "<" + message.getTopic() + "," + message.getContent() + ">";
			
			try {
				output.write(msg.getBytes());
				output.flush();
			} catch(Exception ex){
				ex.printStackTrace();
			}
		}
	}
	
	@Override
	public IMsg receiveMsg() throws InterruptedException {
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		return !queue.isEmpty();
	}

	/**
	 * Handle an event on the serial port. Read the data and print it.
	 */
	public synchronized void serialEvent(SerialPortEvent oEvent) {
		if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				String msg = input.readLine();
				Pattern pattern = Pattern.compile("<{1}[a-zA-z]+,{1}\\w*>{1}", Pattern.CASE_INSENSITIVE);
				Matcher matcher = pattern.matcher(msg);
				
				
				while (matcher.find()) {					
					String[] string = matcher.group().substring(1, matcher.group().length()-1).split(",");					
					IMsg message = string.length < 2 ? new Msg(string[0]) : new Msg(string[0], string[1]);					
					queue.put(message);
		        }
				
			} catch (Exception e) {
				System.err.println(e.toString());
			}
		}
	}

}
