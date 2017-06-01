#include "switch.h"

bool switch_will_return = false;
bool switch_init_wascalled = false;

void switch_mock_init(void) {
  switch_will_return = false;
  switch_init_wascalled = false;
}

void switch_init(void) { switch_init_wascalled = true; }

bool switch_init_called(void) { return switch_init_wascalled; }

bool switch_state(void) { return switch_will_return; }

void switch_state_will_return(bool value) { switch_will_return = value; }
