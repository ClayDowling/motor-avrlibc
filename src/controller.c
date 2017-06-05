#include "controller.h"
#include "motor.h"
#include "switch.h"

/**
 * States I care about:
 *
 * 1. Just started
 * 2. Switch is on and max_position is unset.
 * 3. Switch is on and max_position is set.
 * 4. Position is at zero.
 */

struct motor_state_t MOTOR_STATE;

void setup(void) {
  motor_speed_init();
  motor_up_init();
  motor_down_init();
  switch_init();
  state_just_started();
}

void loop(void) {
  switch (MOTOR_STATE.direction) {
  case UP:
    MOTOR_STATE.position++;
    break;
  case DOWN:
    MOTOR_STATE.position--;
    break;
  default:
    break;
  }
  if (switch_state()) {
    state_switch_on();
  }
}

void state_just_started(void) {
  MOTOR_STATE.direction = UP;
  MOTOR_STATE.position = 0;
  MOTOR_STATE.max_position = UNSET;
}

void state_position_zero(void) {
  MOTOR_STATE.direction = UP;
  motor_down_off();
  motor_up_on();
}

void state_switch_on(void) {
  motor_up_off();
  motor_down_on();
  MOTOR_STATE.direction = DOWN;
  if (UNSET == MOTOR_STATE.max_position) {
    MOTOR_STATE.max_position = MOTOR_STATE.position;
  }
}
