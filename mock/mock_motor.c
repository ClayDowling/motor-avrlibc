#include "mock.h"
#include "motor.h"

void motor_speed_init(void) { mock_register_call(motor_speed_init); }
void motor_up_init(void) { mock_register_call(motor_up_init); }
void motor_down_init(void) { mock_register_call(motor_down_init); }
void motor_up_on(void) { mock_register_call(motor_up_on); }
void motor_up_off(void) { mock_register_call(motor_up_off); }
void motor_down_on(void) { mock_register_call(motor_down_on); }
void motor_down_off(void) { mock_register_call(motor_down_off); }
void motor_speed_set(uint8_t value) {
  mock_register_call_with(motor_speed_set, value);
}
