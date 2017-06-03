#include "controller.h"
#include "motor.h"
#include "switch.h"

void setup(void) {
  motor_speed_init();
  motor_forward_init();
  motor_reverse_init();
  switch_init();
}

void loop(void) {
  motor_reverse_off();
  motor_forward_on();
  motor_speed_set(MOTOR_SPEED);
}
