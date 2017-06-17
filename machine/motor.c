#include "motor.h"
#include <Arduino.h>

/* Speed Control: 3
 * motor_up: 7
 * motor_down: 8
 */

#define PIN_SPEED 3
#define PIN_UP 7
#define PIN_DOWN 8

void motor_speed_init(void) { pinMode(OUTPUT, PIN_SPEED); }
void motor_up_init(void) { pinMode(OUTPUT, PIN_UP); }
void motor_down_init(void) { pinMode(OUTPUT, PIN_DOWN); }

void motor_up_on(void) { digitalWrite(PIN_UP, HIGH); }
void motor_up_off(void) { digitalWrite(PIN_UP, LOW); }

void motor_down_on(void) { digitalWrite(PIN_DOWN, HIGH); }
void motor_down_off(void) { digitalWrite(PIN_DOWN, LOW); }

void motor_speed_set(uint8_t value) { analogWrite(PIN_SPEED, value); }
