#include "Context.h"
#include "kernel/config.h"

Context::Context(){
    this->state = State::AUTOMATIC;
}

void Context::setState(State s){
    state = s;
}

State Context::getState(){
    return state;
}

void Context::reset(){
    state = State::AUTOMATIC;
}

