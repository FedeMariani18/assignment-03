package serial;

import java.util.concurrent.*;
import jssc.*;

/**
 * Comm channel implementation based on serial port.
 * 
 * @author aricci
 *
 */
public class SerialCommChannel implements CommChannel, SerialPortEventListener {

	private SerialPort serialPort;
	private BlockingQueue<String> queue;
	private StringBuffer currentMsg = new StringBuffer();
	
	public SerialCommChannel(String port, int rate) throws Exception {
		queue = new ArrayBlockingQueue<String>(100);

		try {
			serialPort = new SerialPort(port);
			serialPort.openPort();
	
			serialPort.setParams(rate,
			                         SerialPort.DATABITS_8,
			                         SerialPort.STOPBITS_1,
			                         SerialPort.PARITY_NONE);
	
			serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_NONE);
	
			// serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
			serialPort.addEventListener(this);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	@Override
	public void sendMsg(String msg) {
		try {
			synchronized (serialPort) {
				serialPort.writeString(msg + "\n");
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		return !queue.isEmpty();
	}

	/**
	 * This should be called when you stop using the port.
	 * This will prevent port locking on platforms like Linux.
	 */
	public void close() {
		try {
			if (serialPort != null) {
				serialPort.removeEventListener();
				serialPort.closePort();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}


	public void serialEvent(SerialPortEvent event) {
		/* if there are bytes received in the input buffer */
		if (event.isRXCHAR()) {
            try {
            		String msg = serialPort.readString(event.getEventValue());
            		msg = msg.replaceAll("\r", "");
            		currentMsg.append(msg);
            		
        			while (true) {
						int index = currentMsg.indexOf("\n");
						if (index < 0) break;  // there's no newLine in the buffer
						String completeMsg = currentMsg.substring(0, index);
						queue.put(completeMsg);  // put the complete message in the queue
						currentMsg.delete(0, index + 1); // remove the processed message from the buffer
					}
        			
            } catch (Exception ex) {
            		ex.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
	}
}