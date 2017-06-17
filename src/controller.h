#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#define MOTOR_SPEED 120
#define UNSET -1

enum motor_direction_t { UP, DOWN, NODIRECTION };

extern struct motor_state_t {
  enum motor_direction_t direction;
  unsigned long last_check;
  unsigned long duration;
} MOTOR_STATE;

void setup(void);
void loop(void);

void state_just_started(void);
void state_bottom(void);
void state_switch_on(void);

#endif
