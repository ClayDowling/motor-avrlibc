#include "switch.h"
#include <avr/io.h>

/**
 * Input pin is PD2, Chip in 32, Arduino pin D2
 */

void switch_init(void) { DDRD &= ~(_BV(PD2)); }

bool switch_state(void) { return PIND & _BV(PD2); }
