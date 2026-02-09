#include "LCDTask.h"
#include "kernel/config.h"

LCDTask::LCDTask(LiquidCrystal_I2C* lcd, Context& context, int& gradi):
    lcd(lcd), context(context), gradi(gradi){
        lastdegrees = 0;
        lastState = State::AUTOMATIC;
}

void LCDTask::tick(){
    State currentState = context.getState();
    if(currentState != lastState || gradi != lastdegrees){
        switch(currentState){
            case State::AUTOMATIC:
                printString("AUTOMATIC Gradi: " + String(gradi));
                break;
            case State::MANUAL:
                printString("MANUAL Gradi: " + String(gradi));
                break;
            case State::UNCONNECTED:
                printString("UNCONNECTED Gradi: " + String(gradi));
                break;
        }
        lastdegrees = gradi;
        lastState = currentState;
    }
}

void LCDTask::printString(String s){
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(s);
}