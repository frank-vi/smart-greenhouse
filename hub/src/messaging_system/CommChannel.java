package messaging_system;

/**
 * Simple interface for an async msg communication channel
 * @author aricci, francesco.vignola
 *
 */
public interface CommChannel {
	
	/**
	 * To open the communication.
	 */
	void connect() throws Exception;
	
	/**
	 * To stop the communication.
	 */
	void close() throws Exception;
	
	/**
	 * To send an message.
	 * 
	 * Asynchronous model.
	 * 
	 * @param msg
	 */
	void sendMsg(IMsg msg);
	
	/**
	 * To check if a message is available.
	 * 
	 * @return
	 */
	boolean isMsgAvailable();
	
	/**
	 * To receive a message. 
	 * 
	 * Blocking behaviour.
	 */
	IMsg receiveMsg() throws InterruptedException;

}
