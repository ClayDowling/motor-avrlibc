#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#define MOTOR_SPEED 120
#define UNSET -1

enum motor_direction_t { UP, DOWN, NODIRECTION };

extern struct motor_state_t {
  enum motor_direction_t direction;
  int position;
  int max_position;
} MOTOR_STATE;

void setup(void);
void loop(void);

void state_just_started(void);
void state_position_zero(void);
void state_switch_on(void);

#endif
