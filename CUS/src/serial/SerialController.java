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
            String stateToken = parts[0];
            String valveToken = parts.length > 1 ? parts[1] : "";

            Common.State s = Common.stringToState(stateToken);
            if(s != null) {
                controller.setState(s);
            }

            if(!valveToken.isEmpty()){
                int degrees = Integer.parseInt(valveToken);
                controller.setValveOpening(degrees);
            }
        }
    }

    private void sendMsg() {
        String msg = "";
        if(controller.getState() == Common.State.AUTOMATIC){
            msg = Common.stateToString(controller.getState()) + ";";
        } else if (controller.getState() == Common.State.MANUAL){
            msg = Common.stateToString(controller.getState()) + ";" + controller.getValveOpening();
        }

        if(!msg.isEmpty()){
            commChannel.sendMsg(msg);
        }
    }
}
