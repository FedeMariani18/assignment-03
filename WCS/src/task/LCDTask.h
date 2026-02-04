#ifndef __LCD_TASK__
#define __LCD_TASK__

#include <Arduino.h>
#include "kernel\Task.h"
#include "model\Context.h"
#include "LiquidCrystal_I2C.h"

class LCDTask: public Task{
    public:
        LCDTask(LiquidCrystal_I2C* lcd, Context& context, int& gradi);
        void tick();

    private:
        LiquidCrystal_I2C* lcd;
        Context& context;
        int& gradi;
        State lastState;
        void printString(String s);
};
#endif