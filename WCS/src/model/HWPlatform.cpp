#include <Arduino.h>
#include "HWPlatform.h"
#include "devices/button/ButtonImpl.h"
#include "devices/servoMotor/ServoMotorImpl.h"

void wakeUp(){}

HWPlatform::HWPlatform(){
  changeModeButton = new ButtonImpl(BTN_PIN);
  servo = new ServoMotorImpl(SERVO_PIN);

  lcd = new LiquidCrystal_I2C(LCD_ADRR, LCD_COLS, LCD_ROWS);
  lcd->init();
  lcd->backlight();
}

void HWPlatform::init(){}

Button* HWPlatform::getChangeModeButton(){
  return changeModeButton;
}


ServoMotor* HWPlatform::getServo(){
  return servo;
}

LiquidCrystal_I2C* HWPlatform::getLcd(){
  return lcd;
}
