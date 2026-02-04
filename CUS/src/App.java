import core.SystemController;
import http.HttpServerModule;
import mqtt.MQTTSubscriber;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
        SystemController core = new SystemController();
        
        HttpServerModule http = new HttpServerModule(8080, core);
        http.start();
        MQTTSubscriber mqtt = new MQTTSubscriber(core);
        mqtt.start();

        Thread.currentThread().join();
    }
}
