#include "controller.h"
#include "motor.h"
#include "state_transition.h"
#include "switch.h"
#include "timer.h"

/**
 * States I care about:
 *
 * 1. Just started
 * 2. Switch is on and max_position is unset.
 * 3. Switch is on and max_position is set.
 * 4. Position is at zero.
 */

struct motor_state_t MOTOR_STATE;

unsigned long time_expired() { return timer_value() - MOTOR_STATE.last_check; }

void setup(void) {
  motor_speed_init();
  motor_up_init();
  motor_down_init();
  switch_init();
  state_just_started();
  state_position_zero();
}

void loop(void) {
  if (switch_state()) {
    state_switch_on();
  }
  if (DOWN == MOTOR_STATE.direction &&
      (time_expired() > MOTOR_STATE.duration)) {
    state_position_zero();
  }
}

void state_just_started(void) {
  MOTOR_STATE.direction = UP;
  MOTOR_STATE.last_check = timer_value();
  MOTOR_STATE.duration = UNSET;
}
