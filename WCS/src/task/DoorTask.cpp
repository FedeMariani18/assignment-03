#include "task/DoorTask.h"

DoorTask::DoorTask(Context& context, ServoMotor* motor, int& gradi):
context(context), motor(motor), gradi(gradi){
    currentAngle = 0;
}

void DoorTask::init(int period) {
    Task::init(period);
    motor->on();
}

void DoorTask::tick(){
    State s = context.getState();
    int target;

    if (s == State::UNCONNECTED) {
        motor->off();
        return;
    }

    if (!motor->isOn()) {
        motor->on();
    }

    if (s == State::MANUAL || s == State::AUTOMATIC) {
        target = gradi;
    } else {
        target = 0;
    }

    if (currentAngle < target) currentAngle++;
    else if (currentAngle > target) currentAngle--;

    motor->setPosition(currentAngle);

}
