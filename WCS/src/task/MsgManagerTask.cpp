#include "task/MsgManagerTask.h"
#include "kernel/config.h"

MsgManagerTask::MsgManagerTask(Context& context, int& gradi):
    context(context), gradi(gradi){

}

void MsgManagerTask::init(int period){
    Task::init(period);
    MsgService.init();
}

void MsgManagerTask::tick(){
    receive();
    send();
}

void MsgManagerTask::receive(){
    Serial.println("Ricevo");
    if(MsgService.isMsgAvailable()){
        String msg = MsgService.receiveMsg()->getContent();
        Serial.println("Ricevo");
        if (msg.length() > 0) {
            Serial.println(msg);
            int sep = msg.indexOf(';');
            String stateToken = msg.substring(0, sep);
            String degreesToken = msg.substring(sep + 1); 
            State newState = transformMsgToState(stateToken, degreesToken);
            context.setState(newState);
        }
    }
}

void MsgManagerTask::send() {
    String msg = "";
    bool stateChanged = (lastState != context.getState());
    bool degreesChanged = (lastDegrees != gradi);

    if (stateChanged || (context.getState() == State::MANUAL && degreesChanged)) {

        // Stato sempre presente
        msg += transformStateToSring(context.getState()) + ";";

        // Gradi solo in MANUAL
        if (context.getState() == State::MANUAL) {
            msg += (String)gradi;
        }

        // Aggiorno i valori "last"
        lastState = context.getState();
        lastDegrees = gradi;
    }

    if (msg.length() > 0) {
        MsgService.sendMsg(msg);
    }
}

State MsgManagerTask::transformMsgToState(String msg, String degrees){;

    if (msg.equals("MANUAL")) {
        return State::MANUAL;
    } else if (msg.equals("AUTOMATIC")) {
        gradi = degrees.toInt();
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
}