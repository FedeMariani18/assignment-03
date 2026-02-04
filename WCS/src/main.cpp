#include <Arduino.h>
#include "kernel/config.h"
#include "kernel/Scheduler.h"

#include "model/HWPlatform.h"
#include "model/Context.h"

#include "task/ChangeModeButtonTask.h"
#include "task/PotentiometerTask.h"
#include "task/LCDTask.h"
#include "task/MsgManagerTask.h"
#include "task/DoorTask.h"

Scheduler sched;
HWPlatform hWPlatform;
Context context;

int degrees;
// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  sched.init(PERIOD);

  hWPlatform.init();

  Task* changeModeButtonTask = new ChangeModeButtonTask(context, hWPlatform.getChangeModeButton());
  changeModeButtonTask->init(BUTTON_TASK_PERIOD);

  Task* potentiometerTask = new PotentiometerTask(context, hWPlatform.getPot(), degrees);
  potentiometerTask->init(POTENTIOMETER_TASK_PERIOD);

  Task* lcdTask = new LCDTask(hWPlatform.getLcd(), context, degrees);
  lcdTask->init(LCD_TASK_PERIOD);

  Task* msgManagerTask = new MsgManagerTask(context, degrees);
  msgManagerTask->init(MSG_MANAGER_TASK_PERIOD);

  Task* doorTask = new DoorTask(context, hWPlatform.getServo(), degrees);
  doorTask->init(DOOR_TASK_PERIOD);

  sched.addTask(changeModeButtonTask);
  sched.addTask(potentiometerTask);
  sched.addTask(lcdTask);
  sched.addTask(msgManagerTask);
  sched.addTask(doorTask);
}


void loop() {
  // put your main code here, to run repeatedly:
  sched.schedule();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}