#ifndef __CONFIG__
#define __CONFIG__

#include <Arduino.h>

// PIN

#define BTN_PIN 2
#define SERVO_PIN 9
#define POT_PIN A0


// PERIOD

#define PERIOD 10
#define BUTTON_TASK_PERIOD 100
#define POTENTIOMETER_TASK_PERIOD 50
#define LCD_TASK_PERIOD 250
#define MSG_MANAGER_TASK_PERIOD 250
#define DOOR_TASK_PERIOD 50

// LCD

#define LCD_ADRR 0x27
#define LCD_COLS 20
#define LCD_ROWS 2

// BUTTON
#define DEBOUNCE_DELAY 250UL    // ms

// STATE
enum class State {
    AUTOMATIC,
    MANUAL,
    UNCONNECTED
};

#endif