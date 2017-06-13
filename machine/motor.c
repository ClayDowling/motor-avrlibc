#include "motor.h"
#include <avr/io.h>

/* PWM Pin: Timer OC0A, Port Pin PD6, Chip pin 10, Arduino pin D6
 *
 * Up pin: Port Pin PB7, Chip pin 11, Arduino pin D7
 * Down pin: Port Pin PD4, Chip pin 2, Arduino pin D4
 */

void motor_speed_init(void) {
  DDRD |= (1 << DDD6);
  // Making PD6 an output

  OCR0A = 128; // 50% Duty Cycle

  TCCR0A |= (1 << COM0A1); // Non-inverting mode
  TCCR0A |=
      (1 << WGM02) | (1 << WGM00); // Phase Corrected PWM mode top os OCR0A
  TCCR0B |= (1 << CS01);           // Set prescalar to 8 and starts PWM
}
void motor_up_init(void) { DDRB |= _BV(PB7); }
void motor_down_init(void) { DDRD |= _BV(PD4); }

void motor_up_on(void) { PORTB |= _BV(PB7); }
void motor_up_off(void) { PORTB &= ~(_BV(PB7)); }

void motor_down_on(void) { PORTD |= _BV(PD4); }
void motor_down_off(void) { PORTD &= ~(_BV(PD4)); }

void motor_speed_set(uint8_t value) { OCR0A = value; }
