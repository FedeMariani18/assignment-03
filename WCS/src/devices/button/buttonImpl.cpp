#include "ButtonImpl.h"
#include "Arduino.h"
#include "kernel/config.h"

ButtonImpl::ButtonImpl(int pin)
 : pin(pin), lastPressTimestamp(0), currentState(false), lastState(false), pressed(false)
{
  pinMode(pin, INPUT);
  this->currentState = digitalRead(pin);
  this->lastState = this->currentState;
}

void ButtonImpl::update()
{
  bool reading = digitalRead(this->pin);
  unsigned long currentTime = millis();

  if (reading != this->lastState) {
    if ((currentTime - this->lastPressTimestamp) > DEBOUNCE_DELAY) {
      this->lastPressTimestamp = currentTime;
      if (reading == LOW) { // Using LOW because of pull-up resistor
        this->pressed = true;
      }
    }
  }

  this->lastState = reading;
}

bool ButtonImpl::wasPressed()
{
  if (this->pressed) {
    this->pressed = false;
    return true;
  }
  return false;
}

void ButtonImpl::resetPressed()
{
  this->pressed = false;
}

