#ifndef __POTENTIOMETER_TASK__
#define __POTENTIOMETER_TASK__

#include "kernel/Task.h"
#include "devices/potentiometer/Pot.h"
#include "model/Context.h"

class PotentiometerTask: public Task {
    public:
        PotentiometerTask(Context& context, Potentiometer* pot, int& degrees);
        void tick();

    private:
        Context& context;
        Potentiometer* pot;

        int& gradi;
};

#endif