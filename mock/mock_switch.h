#ifndef _MOCK_SWITCH_H_
#define _MOCK_SWITCH_H_

#include "../machine/switch.h"
#include <stdbool.h>

void switch_mock_init(void);

bool switch_init_called(void);

void switch_state_will_return(bool);

#endif
