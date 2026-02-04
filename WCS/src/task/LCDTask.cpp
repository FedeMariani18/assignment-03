#include "LCDTask.h"
#include "kernel/config.h"

LCDTask::LCDTask(LiquidCrystal_I2C* lcd, Context& context, int& gradi):
    lcd(lcd), context(context), lastState(State::AUTOMATIC), gradi(gradi){

}

void LCDTask::tick(){
    State currentState = context.getState();
    if(currentState != lastState){
        switch(currentState){
            case State::AUTOMATIC:
                printString("AUTOMATIC \n Gradi: " + String(gradi));
                break;
            case State::MANUAL:
                printString("MANUAL \n Gradi: " + String(gradi));
                break;
            case State::UNCONNECTED:
                printString("UNCONNECTED \n Gradi: " + String(gradi));
                break;
        }
    
        lastState = currentState;
    }
}

void LCDTask::printString(String s){
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(s);
}