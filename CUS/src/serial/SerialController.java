package serial;

import interfaces.ControlInterface;

public class SerialController {
    private ControlInterface controller;
    private SerialCommChannel commChannel;

    public SerialController(ControlInterface controller, String port) throws Exception {
        this.controller = controller;
        commChannel = new SerialCommChannel(port, 115200);
    }

    public void loop() throws InterruptedException {
        while(true){
            update();
        }
    }

    private void update() {
        
    }
}
