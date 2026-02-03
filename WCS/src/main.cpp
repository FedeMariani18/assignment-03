#include <Arduino.h>
#include "kernel/config.h"
#include "kernel/Scheduler.h"

#include "model/HWPlatform.h"
#include "model/Context.h"

#include "task/ChangeModeButtonTask.h"

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
}

void loop() {
  // put your main code here, to run repeatedly:
  sched.schedule();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}