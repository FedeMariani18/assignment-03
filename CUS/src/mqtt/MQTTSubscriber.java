package mqtt;

import org.eclipse.paho.client.mqttv3.*;

import core.Common.State;
import interfaces.ControlInterface;

public class MQTTSubscriber {

    private ControlInterface controller;
    private final String broker;
    private final String topic;
    private final String clientId;
    private MqttClient client;

    public MQTTSubscriber(ControlInterface controller) {
        this.controller = controller;
        this.broker = "tcp://broker.mqtt-dashboard.com"; //broker pubblico a cui collegarsi
        this.clientId = "esiot-2025-" + System.currentTimeMillis(); //client id, deve essere unico nella connessione
        this.topic = "tms/waterLevel"; //topic su cui, all'interno del broker, verranno ricevuti i messaggi
    }

    public void start() throws MqttException {
        //client mqtt, setto il broker e l'id
        client = new MqttClient(broker, clientId);

        //callback asincrona per la gestione degli eventi mqtt
        client.setCallback(new MqttCallback() {

            //evento di connessione persa
            @Override
            public void connectionLost(Throwable cause) {
                controller.setState(State.UNCONNECTED);
            }

            //evento di messaggio ricevuto
            @Override
            public void messageArrived(String topic, MqttMessage message) {
                String payload = new String(message.getPayload());
                float level = Float.parseFloat(payload);
                controller.setWaterLevel(level);
            }

            //evento di avvenuta consegna, non ci serve visto che siamo solo dei subscriber
            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {}
        });

        client.connect();
        //sottoscrizione al topic con qos 1 (at least once)
        client.subscribe(topic, 1);
    }
}
