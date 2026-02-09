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
Sonar sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, SONAR_TIMEOUT);
WiFiClient espClient;
PubSubClient mqttClient(espClient);
volatile bool isConnOk = false;
volatile float waterLevel;
bool wifiConnecting = false;


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

void loop() {}

void SonarTaskCode(void* parameter){
  Serial.print("SonarTask is running on core ");
  Serial.println(xPortGetCoreID());

  const TickType_t period = SONAR_TASK_PERIOD / portTICK_PERIOD_MS;
  TickType_t lastWakeTime = xTaskGetTickCount();

  for(;;){
    waterLevel = TANK_HEIGHT- sonar.getDistance();
    vTaskDelayUntil(&lastWakeTime, period);
  }
}

void ComunicationTaskCode(void* parameter){
  Serial.print("ComunicationTask is running on core ");
  Serial.println(xPortGetCoreID());

  const TickType_t period = COMUNICATION_TASK_PERIOD / portTICK_PERIOD_MS;
  TickType_t lastWakeTime = xTaskGetTickCount();

  enum ComunicationState {
    CONNECTED,
    UNCONNECTED
  };

  ComunicationState state = UNCONNECTED;
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  String clientId = "esiot-2025-client-" + String(random(0xffff), HEX);

  for(;;) {
    String msg;
    switch (state) {
      case CONNECTED:
        if (WiFi.status() != WL_CONNECTED || !mqttClient.connected()) {
          isConnOk = false;
          state = UNCONNECTED;
          break;
        }
        isConnOk = true;
        mqttClient.loop();
        msg = String(waterLevel);
        mqttClient.publish(MQTT_TOPIC, msg.c_str());
        break;
      case UNCONNECTED:
        if (WiFi.status() != WL_CONNECTED) {
          if (!wifiConnecting) {
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            wifiConnecting = true;
            Serial.println("WiFi connecting...");
          }
        } else {
          wifiConnecting = false;
          if (mqttClient.connect(clientId.c_str())) {
            state = CONNECTED;
            isConnOk = true;
            Serial.println("MQTT connected");
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
        if (!isConnOk) {
          state = UNCONNECTED;
          greenLed.switchOff();
          redLed.switchOn();
        }
        break;
      case UNCONNECTED:
        if (isConnOk) {
          state = CONNECTED;
          greenLed.switchOn();
          redLed.switchOff();
        }
        break;
    }

    vTaskDelayUntil(&lastWakeTime, period);
  }
}

