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
    msgAvailable = false;
    return currentMsg;
}

void MsgServiceClass::init(){
    Serial.begin(115200);
    content.reserve(256);
    currentMsg = new Msg("");
    resetMsg();
}

void MsgServiceClass::resetMsg(){
    msgAvailable = false;
}

void MsgServiceClass::sendMsg(const String& msg){
    Serial.println(msg);
}

void serialEvent() {
    while (Serial.available()) {
        char ch = (char) Serial.read();
        if (ch == '\n'){
            MsgService.currentMsg = new Msg(content); // Usa l'oggetto esistente
            MsgService.msgAvailable = true;      
            content = ""; // SVUOTA SUBITO IL BUFFER PER IL PROSSIMO MESSAGGIO
        } else if (ch != '\r'){ // Ignora il ritorno a capo di Windows
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