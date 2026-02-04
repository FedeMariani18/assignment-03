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
        this.broker = "tcp://broker.mqtt-dashboard.com";
        this.clientId = "esiot-2025-" + System.currentTimeMillis();
        this.topic = "tms/waterLevel";
    }

    public void start() throws MqttException {
        controller.setLastMessageTimeFromTMS(System.currentTimeMillis());
        client = new MqttClient(broker, clientId);

        client.setCallback(new MqttCallback() {

            @Override
            public void connectionLost(Throwable cause) {
                controller.setState(State.UNCONNECTED);
            }

            @Override
            public void messageArrived(String topic, MqttMessage message) {
                controller.setLastMessageTimeFromTMS(System.currentTimeMillis());

                String payload = new String(message.getPayload());
                float level = Float.parseFloat(payload);
                controller.setWaterLevel(level);
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {}
        });

        client.connect();
        client.subscribe(topic, 1);
    }
}
