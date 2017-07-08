#include "controller.h"
#include "motor.h"
#include "state_transition.h"
#include "switch.h"
#include "timer.h"

// States of Interes
//
// 1. Just started (in setup).  Initialization of the various components must
//    happen and we must flow into state_bottom (below)
// 2. state_bottom: The ornament is at the bottom of the string, fully extended
//    out from the pulley.
// 3. state_switch_on: The limit switch is close (i.e. on), implying that the
//    ornament is as close as it can get to the pulley.  You should definitely
//    turn the motor off at this point, or something will break.

struct motor_state_t MOTOR_STATE;

/**
 * Measures the time expired (in milliseconds) since the last time we had a
 * significant time event (i.e. MOTOR_STATE.last_check)
 */
unsigned long elapsed_time() { return timer_value() - MOTOR_STATE.last_state_change; }

void setup(void) {
  // Left as an exercise for the reader.
  //
  // See functions definite in machine/switch.h and machine/motor.h
}

void loop(void) {
  // Left as an exercise for the reader
  //
  // See functions defined in state_transition.h (in this folder)
}
