#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "LiquidCrystal_I2C.h"
#include "kernel/config.h"
#include "devices/button/Button.h"
#include "devices/servoMotor/ServoMotor.h"
#include "devices/potentiometer/Pot.h"

class HWPlatform {

public:
  HWPlatform();
  void init();

  Button* getChangeModeButton();
  Potentiometer* getPot();
  ServoMotor* getServo();
  LiquidCrystal_I2C* getLcd();
  

private:
  Button* changeModeButton;
  Potentiometer* pot;
  ServoMotor* servo;
  LiquidCrystal_I2C* lcd;
};

#endif
