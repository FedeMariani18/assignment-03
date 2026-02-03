#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "LiquidCrystal_I2C.h"
#include "kernel/config.h"
#include "devices/button/Button.h"
#include "devices/servoMotor/ServoMotor.h"

class HWPlatform {

public:
  HWPlatform();
  void init();

  Button* getChangeModeButton();
  ServoMotor* getServo();
  LiquidCrystal_I2C* getLcd();
  

private:
  Button* changeModeButton;
  ServoMotor* servo;
  LiquidCrystal_I2C* lcd;
};

#endif
