#include "state_transition.h"
#include "controller.h"
#include "motor.h"
#include "timer.h"
#include <stdlib.h>

void state_bottom(void) {
  MOTOR_STATE.direction = UP;
  motor_down_off();
  timer_wait((random() % 117) + 3);
  motor_up_on();
  MOTOR_STATE.last_check = timer_value();

  motor_speed_set(MOTOR_SPEED);
}

void state_switch_on(void) {
  motor_up_off();
  MOTOR_STATE.direction = DOWN;
  timer_wait((random() % 117) + 3);
  motor_down_on();
  MOTOR_STATE.last_check = timer_value();
}
