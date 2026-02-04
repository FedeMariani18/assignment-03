#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"

class ButtonImpl : public Button
{

public:
  ButtonImpl(int pin);
  bool wasPressed();
  void update();
  void resetPressed();

private:
  int pin;
  unsigned long lastPressTimestamp;
  bool currentState;
  bool lastState;
  bool pressed;
};


#endif
