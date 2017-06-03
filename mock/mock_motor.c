#include "mock.h"
#include "motor.h"

void motor_speed_init(void) { mock_register_call(motor_speed_init); }
void motor_forward_init(void) { mock_register_call(motor_forward_init); }
void motor_reverse_init(void) { mock_register_call(motor_reverse_init); }
void motor_forward_on(void) { mock_register_call(motor_forward_on); }
void motor_forward_off(void) { mock_register_call(motor_forward_off); }
void motor_reverse_on(void) { mock_register_call(motor_reverse_on); }
void motor_reverse_off(void) { mock_register_call(motor_reverse_off); }
void motor_speed_set(uint8_t value) {
  mock_register_call_with(motor_speed_set, value);
}
