#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/servoMotor/ServoMotor.h"

class DoorTask : public Task{
public:
    DoorTask(Context& context, ServoMotor* motor, int& gradi);
    void tick() override;

private:
    Context& context;
    ServoMotor* motor;
    int& gradi;

    int currentAngle;
};

#endif