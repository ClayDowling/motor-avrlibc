#include "motor.h"

enum MOTOR_IDX {
  speed_init,
  forward_init,
  reverse_init,
  forward_on,
  forward_off,
  reverse_on,
  reverse_off,
  speed_set,
  MOTOR_MAX
};

uint8_t called[MOTOR_MAX];

void motor_mock_init(void) {
  for (int i = 0; i < MOTOR_MAX; ++i) {
    called[i] = 0;
  }
}

void motor_speed_init(void) { called[speed_init] = true; }
void motor_forward_init(void) { called[forward_init] = true; }
void motor_reverse_init(void) { called[reverse_init] = true; }
void motor_forward_on(void) { called[forward_on] = true; }
void motor_forward_off(void) { called[forward_off] = true; }
void motor_reverse_on(void) { called[reverse_on] = true; }
void motor_reverse_off(void) { called[reverse_off] = true; }
void motor_speed_set(uint8_t value) { called[speed_set] = value; }

bool motor_speed_init_called(void) { return called[speed_init]; }
bool motor_forward_init_called(void) { return called[forward_init]; }
bool motor_reverse_init_called(void) { return called[reverse_init]; }
bool motor_forward_on_called(void) { return called[forward_on]; }
bool motor_forward_off_called(void) { return called[forward_off]; }
bool motor_reverse_on_called(void) { return called[reverse_on]; }
bool motor_reverse_off_called(void) { return called[reverse_off]; }
uint8_t motor_speed_set_called(void) { return called[speed_set]; }
