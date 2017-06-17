#include "mock.h"
#include "state_transition.h"

void state_position_zero(void) { mock_register_call(state_position_zero); }

void state_switch_on(void) { mock_register_call(state_switch_on); }