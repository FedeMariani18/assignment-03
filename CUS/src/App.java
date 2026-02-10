                                                                         import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

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
        serial.start();

        ScheduledExecutorService scheduler =
        Executors.newSingleThreadScheduledExecutor();

        //visto che il cus è event-driven non ha un flusso di controllo, quindi per rilevare non un evento ma 
        // la sua "assenza" è necessario un modo per richiamare periodicamente il check:
        scheduler.scheduleAtFixedRate(() -> {
            core.checkT2();
        }, 0, 500, TimeUnit.MILLISECONDS);

        Thread.currentThread().join();
    }
}
