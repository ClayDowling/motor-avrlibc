#include "mock_timer.h"
#include "mock.h"

#define WILL_RETURN_MAX 20

unsigned long will_return[WILL_RETURN_MAX];
int WILL_RETURN_IDX = 0;
long random_expected_value = 0;

void timer_value_will_return(int num_values, ...) {
  va_list valist;
  int i;

  for (i = 0; i < sizeof(will_return); ++i) {
    will_return[i] = 0;
  }

  va_start(valist, num_values);
  for (i = 0; i < num_values && i < WILL_RETURN_MAX; ++i) {
    will_return[i] = va_arg(valist, unsigned long);
  }
  va_end(valist);
  WILL_RETURN_IDX = 0;
}

unsigned long timer_value(void) {
  mock_register_call(timer_value);
  return will_return[WILL_RETURN_IDX++];
}

void timer_wait(unsigned int seconds) {
  mock_register_call_with(timer_wait, seconds);
}

void random_will_return(long expected_value) {
  random_expected_value = expected_value;
}

long random(void) {
  mock_register_call(random);
  return random_expected_value;
}
