#include "Arduino.h"
#include "config.h"
#include "MsgService.h"

void serialEvent();

String content;
MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(){
    return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg(){
    if (!msgAvailable) {
        return NULL;
    }
    msgAvailable = false;
    return &currentMsg;
}

void MsgServiceClass::init(){
    Serial.begin(115200);
    content.reserve(256);
    resetMsg();
}

void MsgServiceClass::resetMsg(){
    currentMsg.setContent("");
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
            MsgService.currentMsg.setContent(content);
            MsgService.msgAvailable = true;  
            content = "";    
        } else {
            content += ch;      
        }   
    }
}