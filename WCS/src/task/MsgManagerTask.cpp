#include "task/MsgManagerTask.h"
#include "kernel/config.h"

MsgManagerTask::MsgManagerTask(Context& context, int& gradi):
    context(context), gradi(gradi){
    lastState = State::UNCONNECTED;
    lastDegrees = 0;
}

void MsgManagerTask::init(int period){
    Task::init(period);
    MsgService.init();
}

void MsgManagerTask::tick(){
    send();
    receive();
}

void MsgManagerTask::receive(){
    if(MsgService.isMsgAvailable()){
        Msg* m = MsgService.receiveMsg();
        if (m == NULL) return;

        String msg = m->getContent();

        if(msg.length() > 0){
            int sep = msg.indexOf(';');

            if (sep == -1) {
                Serial.println("Messaggio non valido: " + msg);
                return;
            }

            String stateToken = msg.substring(0, sep);
            String degreesToken = msg.substring(sep + 1);

            State newState = transformMsgToState(stateToken);
            context.setState(newState);

            int val = degreesToken.toInt();
            if (val >= 0){
                gradi = val;
            } 
        }
        
        delete m;
    }
}

void MsgManagerTask::send() {
    String msg = "";
    bool stateChanged = (lastState != context.getState());
    bool degreesChanged = (lastDegrees != gradi);

    if (stateChanged || degreesChanged) {

        // Stato sempre presente
        msg += transformStateToSring(context.getState()) + ";" + String(gradi);

        // Aggiorno i valori "last"
        lastState = context.getState();
        lastDegrees = gradi;
    }

    if (msg.length() > 0) {
        MsgService.sendMsg(msg);
    }
}

State MsgManagerTask::transformMsgToState(String msg){
    if (msg.equals("MANUAL")) {
        return State::MANUAL;
    } else if (msg.equals("AUTOMATIC")) {
        return State::AUTOMATIC;
    } else if (msg.equals("UNCONNECTED")) {
        return State::UNCONNECTED;
    }
    return State::UNCONNECTED; //msg not valid
}

String MsgManagerTask::transformStateToSring(State state){
    switch (state)
    {
        case State::MANUAL:
            return "MANUAL";
            break;
    
        case State::AUTOMATIC:
            return "AUTOMATIC";
            break;

        case State::UNCONNECTED:
            return "UNCONNECTED";
            break;
    }

    return "UNCONNECTED";
}