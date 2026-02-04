import core.SystemController;
import http.HttpServerModule;
import mqtt.MQTTSubscriber;
import serial.SerialController;

public class App {
    public static void main(String[] args) throws Exception {
        SystemController core = new SystemController();
        
        HttpServerModule http = new HttpServerModule(8080, core);
        http.start();
        MQTTSubscriber mqtt = new MQTTSubscriber(core);
        mqtt.start();

        String portName = "COM3";
        SerialController serial = new SerialController(core, portName);
        serial.loop();

        Thread.currentThread().join();
    }
}
