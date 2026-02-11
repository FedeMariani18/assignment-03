package serial;

import interfaces.ControlInterface;

import core.Common;
import core.Common.*;

public class SerialController {
    private ControlInterface controller;
    private SerialCommChannel commChannel;
    private State lastState;
    private int lastDegrees;
    private Boolean first = true; 

    public SerialController(ControlInterface controller, String port) throws Exception {
        this.controller = controller;
        commChannel = new SerialCommChannel(port, 115200);
        lastState = null;
        lastDegrees = -1;
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
            Thread.sleep(1000);
        }
    }

    private void processIO() throws InterruptedException{
        updateFromMsg();
        sendMsg();
    }

    private void updateFromMsg() throws InterruptedException {
        if(commChannel.isMsgAvailable()){
            String msg = commChannel.receiveMsg();
            System.out.println(msg);
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
        if(controller.getState() != lastState || controller.getValveOpening() != lastDegrees || first) {
            first = false;
            lastState = controller.getState();
            lastDegrees = controller.getValveOpening();
            String msg = Common.stateToString(controller.getState())
                + ";"
                + controller.getValveOpening();

            if(!msg.isEmpty() && commChannel.isOpen()){
                commChannel.sendMsg(msg);
            }
        }
    }
}
