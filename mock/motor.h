#ifndef _MOCK_MOTOR_H_
#define _MOCK_MOTOR_H_

#include "../machine/motor.h"
#include <stdbool.h>

void motor_mock_init(void);

bool motor_speed_init_called(void);
bool motor_forward_init_called(void);
bool motor_reverse_init_called(void);

bool motor_forward_on_called(void);
bool motor_forward_off_called(void);
bool motor_reverse_on_called(void);
bool motor_reverse_off_called(void);
uint8_t motor_speed_set_called(void);

#endif
