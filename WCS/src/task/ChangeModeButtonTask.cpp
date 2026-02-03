#include "task/ChangeModeButtonTask.h"


ChangeModeButtonTask::ChangeModeButtonTask(Context& context, Button* button): 
    context(context), button(button){

}

void ChangeModeButtonTask::tick() {
    if(button->isPressed()){
        if(this->context.getState() == State::AUTOMATIC){
            this->context.setState(State::MANUAL);
        } else if(this->context.getState() == State::MANUAL){
            this->context.setState(State::AUTOMATIC);
        } 
    }
}