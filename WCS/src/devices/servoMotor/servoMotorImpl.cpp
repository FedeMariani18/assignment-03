#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin){
    this->pin = pin;  
    _on = false;
}

void ServoMotorImpl::on(){
    _on = true;
    motor.attach(pin);
}

bool ServoMotorImpl::isOn(){
    return _on;
}

void ServoMotorImpl::setPosition(int angle){
    if(angle > 180) {
        angle = 180;
    } else if (angle < 0) {
        angle = 0;
    }

    float coeff = (2400.0-544.0)/180;
    motor.write(544 + angle*coeff);
}

void ServoMotorImpl::off(){
    _on = false;
    motor.detach();
}