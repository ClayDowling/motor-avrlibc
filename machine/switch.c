#include "switch.h"
#include <Arduino.h>

#define PIN_SWITCH 12

void switch_init(void) { pinMode(PIN_SWITCH, INPUT_PULLUP); }

bool switch_state(void) { return digitalRead(PIN_SWITCH) == HIGH; }
