#include "task/PotentiometerTask.h"

PotentiometerTask::PotentiometerTask(Context& context, Potentiometer* pot, int& degrees):
    context(context), pot(pot), gradi(degrees){
    lastDegrees = 0;
    stableDegrees = 0;
    lastChangeTime = 0;
}

void PotentiometerTask::tick(){
    if(context.getState() == State::MANUAL){
        pot->sync();
        int currentReadDegrees = (int)(pot->getValue() * 100);
        
        unsigned long now = millis();

        if(abs(currentReadDegrees - lastDegrees) >= TOLLERANCE) {
            lastDegrees = currentReadDegrees;
            lastChangeTime = now;
        }
        
        //the pot change value only if is stable for 1 second
        if (abs(lastDegrees - stableDegrees) >= TOLLERANCE &&
            (now - lastChangeTime) > STABLE_TIME) {

            stableDegrees = lastDegrees;
            gradi = stableDegrees;
        }
    }
}