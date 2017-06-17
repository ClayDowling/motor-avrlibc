#include "timer.h"
#include <Arduino.h>

unsigned long timer_value(void) { return millis(); }

void timer_wait(unsigned int seconds) {
  unsigned long target = timer_value() + (1000 * seconds);
  while (target > timer_value())
    ;
}
