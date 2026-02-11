#include "task/ChangeModeButtonTask.h"


ChangeModeButtonTask::ChangeModeButtonTask(Context& context, Button* button): 
    context(context), button(button){

}

void ChangeModeButtonTask::tick() {
    button->update();
    if(button->wasPressed()){
        if(context.getState() == State::AUTOMATIC){
            context.setState(State::MANUAL);
        } else if(context.getState() == State::MANUAL){
            context.setState(State::AUTOMATIC);
        } 
    }
}