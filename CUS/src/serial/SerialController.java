package serial;

import interfaces.ControlInterface;
import core.Common;

public class SerialController {
    private ControlInterface controller;
    private SerialCommChannel commChannel;

    public SerialController(ControlInterface controller, String port) throws Exception {
        this.controller = controller;
        commChannel = new SerialCommChannel(port, 115200);
    }

    public void start() {
        new Thread(() -> {
            try {
                loop();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }).start();
    }

    public void loop() throws InterruptedException {
        while(true){
            processIO();
            Thread.sleep(10);
        }
    }

    private void processIO() throws InterruptedException{
        updateFromMsg();
        sendMsg();
    }

    private void updateFromMsg() throws InterruptedException {
        if(commChannel.isMsgAvailable()){
            
            String msg = commChannel.receiveMsg();
            String[] parts = msg.split(";");

            if (parts.length < 2) {
                System.out.println("Messaggio seriale non valido: " + msg);
                return;
            }

            String stateToken = parts[0];
            String degreesToken = parts[1];

            Common.State s = Common.stringToState(stateToken);
            if(s != null) {
                controller.setState(s);
            }

            try {
                int degrees = Integer.parseInt(degreesToken);
                controller.setValveOpening(degrees);
            } catch (NumberFormatException e) {
                System.out.println("Gradi non validi nel messaggio: " + msg);
            }

        }
    }

    private void sendMsg() {
        String msg = Common.stateToString(controller.getState())
                    + ";"
                    + controller.getValveOpening();

        if(!msg.isEmpty() && commChannel.isOpen()){
            commChannel.sendMsg(msg);
        }
    }
}
