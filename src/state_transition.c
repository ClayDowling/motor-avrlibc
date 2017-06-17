#include "state_transition.h"
#include "controller.h"

void state_position_zero(void) {
  MOTOR_STATE.direction = UP;
  motor_down_off();
  timer_wait(1);
  motor_up_on();
  motor_speed_set(MOTOR_SPEED);
}

void state_switch_on(void) {
  motor_up_off();
  MOTOR_STATE.direction = DOWN;
  if (UNSET == MOTOR_STATE.duration) {
    MOTOR_STATE.duration = timer_value() - MOTOR_STATE.last_check;
  }
  timer_wait(2);
  motor_down_on();
  MOTOR_STATE.last_check = timer_value();
}