#ifndef __BUTTON_TASK__
#define __BUTTON_TASK__

#include "kernel/Task.h"
#include "devices/button/ButtonImpl.h"
#include "model/Context.h"

class ChangeModeButtonTask: public Task {
    public:
        ChangeModeButtonTask(Context& context, Button* button);
        void tick();

    private:
        Button* button;
        Context& context;
};

#endif