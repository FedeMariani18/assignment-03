#include "Arduino.h"
#include "config.h"
#include "MsgService.h"

void serialEvent();

String content;
MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(){
    serialEvent();
    return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg(){
    Msg* msg = currentMsg;
    resetMsg();
    return msg;
}

void MsgServiceClass::init(){
    Serial.begin(115200);
    content.reserve(256);
    currentMsg = new Msg("");
    resetMsg();
}

void MsgServiceClass::resetMsg(){
    if(currentMsg == NULL){
        currentMsg->setContent("");
    }
    msgAvailable = false;
    content = "";
}

void MsgServiceClass::sendMsg(const String& msg){
    Serial.println(msg);
}

void serialEvent() {
    /* reading the content */
    while (Serial.available()) {
        char ch = (char) Serial.read();
        if (ch == '\n'){
            MsgService.currentMsg = new Msg(content);
            MsgService.msgAvailable = true;      
        } else {
            content += ch;      
        }   
    }
}

bool MsgServiceClass::isMsgAvailable(Pattern& pattern){
    return (msgAvailable && pattern.match(*currentMsg));
}

Msg* MsgServiceClass::receiveMsg(Pattern& pattern){
    if (msgAvailable && pattern.match(*currentMsg)){
        Msg* msg = currentMsg;
        resetMsg();
        return msg;  
    } else {
        return NULL; 
    }
}