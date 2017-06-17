#include "mock.h"
#include "state_transition.h"

void state_bottom(void) { mock_register_call(state_bottom); }

void state_switch_on(void) { mock_register_call(state_switch_on); }