#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>

void motor_speed_init(void);
void motor_up_init(void);
void motor_down_init(void);

void motor_up_on(void);
void motor_up_off(void);
void motor_down_on(void);
void motor_down_off(void);
void motor_speed_set(uint8_t);

#endif
