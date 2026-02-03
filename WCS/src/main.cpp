#include <Arduino.h>
#include "kernel/config.h"
#include "kernel/scheduler.h"

#include "model/HWPlatform.h"
#include "model/context.h"

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


}

void loop() {
  // put your main code here, to run repeatedly:
  sched.schedule();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}