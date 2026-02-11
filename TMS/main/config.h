#ifndef __CONFIG__
#define __CONFIG__

#include <Arduino.h>

#define SONAR_ECHO_PIN 7
#define SONAR_TRIG_PIN 8
#define SONAR_TIMEOUT 1
#define GREEN_LED_PIN 6
#define RED_LED_PIN 5

#define LED_TASK_PERIOD 100
#define SONAR_TASK_PERIOD 100
#define COMUNICATION_TASK_PERIOD 100

#define MQTT_SERVER "broker.mqtt-dashboard.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "tms/waterLevel"
#define WIFI_SSID "iPhone di Fede"
#define WIFI_PASSWORD "12345678"

#define TANK_HEIGHT 2
#endif