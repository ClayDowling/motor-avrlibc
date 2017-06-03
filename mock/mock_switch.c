#include "mock_switch.h"
#include "mock.h"

bool switch_will_return = false;

void switch_mock_init(void) { switch_will_return = false; }

void switch_init(void) { mock_register_call(switch_init); }

bool switch_state(void) {
  mock_register_call(switch_state);
  return switch_will_return;
}

void switch_state_will_return(bool value) { switch_will_return = value; }
