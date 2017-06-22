#include "controller.h"
#include "motor.h"
#include "state_transition.h"
#include "switch.h"
#include "timer.h"

struct motor_state_t MOTOR_STATE;

/**
 * Measures the time expired (in milliseconds) since the last time we had a
 * significant time event (i.e. MOTOR_STATE.last_check)
 */
unsigned long time_expired() { return timer_value() - MOTOR_STATE.last_check; }

void setup(void) {
  motor_speed_init();
  motor_up_init();
  motor_down_init();
  state_just_started();
  state_bottom();
}

void loop(void) {
  if (MOTOR_STATE.direction == UP && time_expired() > MOTOR_DURATION) {
    state_switch_on();
  }
  if (DOWN == MOTOR_STATE.direction && time_expired() > MOTOR_DURATION) {
    state_bottom();
  }
}

void state_just_started(void) {
  MOTOR_STATE.direction = UP;
  MOTOR_STATE.last_check = timer_value();
}
