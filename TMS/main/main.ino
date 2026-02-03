#include "Sonar.h"
#include "Led.h"
#include "config.h"
#include <WiFi.h>
#include <PubSubClient.h>

TaskHandle_t LedTask;
TaskHandle_t SonarTask;
TaskHandle_t ComunicationTask;
Led greenLed(GREEN_LED_PIN);
Led redLed(RED_LED_PIN);
WiFiClient espClient;
PubSubClient mqttClient(espClient);
volatile bool isConnOk = false;
volatile float waterLevel;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  xTaskCreatePinnedToCore(SonarTaskCode, "Sonar", 4096, NULL, 1, &SonarTask, 1);
  xTaskCreatePinnedToCore(ComunicationTaskCode, "MQTT", 8192, NULL, 1, &ComunicationTask, 0);
  xTaskCreatePinnedToCore(LedTaskCode, "LED", 1024, NULL, 1, &LedTask, 1);
  randomSeed(analogRead(0));

}

void loop() {
  // put your main code here, to run repeatedly:

}

void SonarTaskCode(void* parameter){
  Serial.print("SonarTask is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){

  } 
}

void ComunicationTaskCode(void* parameter){
  Serial.print("ComunicationTask is running on core ");
  Serial.println(xPortGetCoreID());

  const TickType_t period = COMUNICATION_TASK_PERIOD / portTICK_PERIOD_MS;
  TickType_t lastWakeTime = xTaskGetTickCount();

  enum ComunicationState {
    CONNECTED,
    DISCONNECTED
  };

  ComunicationState state = DISCONNECTED;
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  String clientId = "esiot-2025-client-" + String(random(0xffff), HEX);

  for(;;) {
    switch (state) {
      case CONNECTED:
        if (WiFi.status() == WL_CONNECTED && mqttClient.connected()) {
          mqttClient.loop();
          String msg = String(waterLevel);
          mqttClient.publish(MQTT_TOPIC, msg.c_str());
          isConnOk = true;
        } else {
          isConnOk = false;
          state = DISCONNECTED;
        }
        break;

      case DISCONNECTED:
        isConnOk = false;
        if (WiFi.status() != WL_CONNECTED) {
          WiFi.begin(SSID, PASSWORD);
        } else {
          if (mqttClient.connect(clientId.c_str())) {
            state = CONNECTED;
          }
        }
        break;
    }

    vTaskDelayUntil(&lastWakeTime, period);
  }
}

void LedTaskCode(void *pvParameters) {
  Serial.print("LedTask is running on core ");
  Serial.println(xPortGetCoreID());

  const TickType_t period = LED_TASK_PERIOD / portTICK_PERIOD_MS;
  TickType_t lastWakeTime = xTaskGetTickCount();
  enum LedState {
    CONNECTED,
    UNCONNECTED
  };
  LedState state = UNCONNECTED;
  for(;;) {
    switch (state) {
      case CONNECTED:
        greenLed.switchOn();
        redLed.switchOff();
        if (!isConnOk) {
          state = UNCONNECTED;
        }
        break;
      case UNCONNECTED:
        greenLed.switchOff();
        redLed.switchOn();
        if (isConnOk) {
          state = CONNECTED;
        }
        break;
    }

    vTaskDelayUntil(&lastWakeTime, period);
  }
}

