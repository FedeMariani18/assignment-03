#include "task/PotentiometerTask.h"

PotentiometerTask::PotentiometerTask(Context& context, Potentiometer* pot, int& degrees):
    context(context), pot(pot), gradi(degrees){
}

void PotentiometerTask::tick(){
    if(context.getState() == State::MANUAL){
        pot->sync();
        gradi = pot->getValue() * 90;
    }
}