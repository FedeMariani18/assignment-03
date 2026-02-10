#ifndef __MESSAGE_TASK__
#define __MESSAGE_TASK__

#include "kernel\Task.h"
#include "kernel\MsgService.h"
#include "model\Context.h"


class MsgManagerTask: public Task{

public:
    MsgManagerTask(Context& context, int& gradi);
    void init(int period) override;
    void tick();

private:
    void receive();
    void send();
    State transformMsgToState(String msg);
    String transformStateToSring(State state);
    Context& context;
    int& gradi;
    int lastDegrees;
    State lastState;
};

#endif