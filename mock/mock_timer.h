#ifndef _MOCK_TIMER_H_
#define _MOCK_TIMER_H_

#include "timer.h"
#include <stdarg.h>

void timer_value_will_return(int num_values, ...);

void random_will_return(long expected_value);

#endif
