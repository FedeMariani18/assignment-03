#ifndef __CONFIG__
#define __CONFIG__

#include <Arduino.h>

// PIN

#define BTN_PIN 2
#define SERVO_PIN 9


// PERIOD

#define PERIOD 10


// LCD

#define LCD_ADRR 0x27
#define LCD_COLS 20
#define LCD_ROWS 2

// STATE
enum class State {
    AUTOMATIC,
    MANUAL,
    UNCONNECTED
};

#endif