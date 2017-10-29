#include "controller.h"
#include "motor.h"
#include "state_transition.h"
#include "switch.h"
#include "timer.h"

struct motor_state_t MOTOR_STATE;

/**
 * Measures the time expired (in milliseconds) since the last time we had a
 * significant time event (i.e. MOTOR_STATE.last_state_change)
 */
unsigned long elapsed_time() { return timer_value() - MOTOR_STATE.last_state_change; }

void setup(void) {
  motor_speed_init();
  motor_up_init();
  motor_down_init();
  state_just_started();
  state_bottom();
}

void loop(void) {
  if (UP == MOTOR_STATE.direction && elapsed_time() > MOTOR_DURATION) {
    state_switch_on();
  }
  if (DOWN == MOTOR_STATE.direction && elapsed_time() > MOTOR_DURATION) {
    state_bottom();
  }
}

void state_just_started(void) {
  MOTOR_STATE.direction = UP;
  MOTOR_STATE.last_state_change = timer_value();
}
