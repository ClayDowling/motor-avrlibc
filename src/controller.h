#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#define MOTOR_SPEED 180
#define MOTOR_DURATION 10000
#define UNSET -1

enum motor_direction_t { UP, DOWN, NODIRECTION };

extern struct motor_state_t {
  enum motor_direction_t direction;
  unsigned long last_state_change;
} MOTOR_STATE;

void setup(void);
void loop(void);

void state_just_started(void);
void state_bottom(void);
void state_switch_on(void);

#endif
