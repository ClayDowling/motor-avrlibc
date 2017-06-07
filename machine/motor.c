#include "motor.h"

void motor_speed_init(void) {
  // PD5/Pin11 is our PWM output OC0B
  TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS00);
  DDRD |= (1 << PD5);
}
void motor_up_init(void);
void motor_down_init(void);

void motor_up_on(void);
void motor_up_off(void);
void motor_down_on(void);
void motor_down_off(void);
void motor_speed_set(uint8_t);
