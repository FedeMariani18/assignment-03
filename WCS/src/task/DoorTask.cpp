#include "task/DoorTask.h"

DoorTask::DoorTask(Context& context, ServoMotor* motor, int& gradi):
context(context), motor(motor), gradi(gradi){
    currentAngle = 0;
}

void DoorTask::tick(){
    State s = context.getState();
    int target;

    if (s == State::MANUAL || s == State::AUTOMATIC) {
        target = gradi;
    } else {
        target = 0;
    }

    if (currentAngle < target) currentAngle++;
    else if (currentAngle > target) currentAngle--;

    motor->setPosition(currentAngle);

}
