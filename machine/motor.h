#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>

void motor_speed_init(void);
void motor_forward_init(void);
void motor_reverse_init(void);

void motor_forward_on(void);
void motor_forward_off(void);
void motor_reverse_on(void);
void motor_reverse_off(void);
void motor_speed_set(uint8_t);

#endif
