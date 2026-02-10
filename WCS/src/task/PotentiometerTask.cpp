#include "task/PotentiometerTask.h"

PotentiometerTask::PotentiometerTask(Context& context, Potentiometer* pot, int& degrees):
    context(context), pot(pot), gradi(degrees){
        lastDegrees = 0;
}

void PotentiometerTask::tick(){
    if(context.getState() == State::MANUAL){
        pot->sync();
        int currentReadDegrees = (int)(pot->getValue() * 90);
        if(abs(currentReadDegrees - lastDegrees) >= 2) {
            lastDegrees = currentReadDegrees;
            gradi = lastDegrees;
        }
    }
}