#ifndef _WHIRLWIND_H_
#define _WHIRLWIND_H_

#include "common_structs.h"

// args: variation
API_CALLABLE(InitActionCommand);

// args: prep time, duration, difficulty
API_CALLABLE(StartActionCommand);

void action_command_whirlwind_update(void);
void action_command_whirlwind_draw(void);
void action_command_whirlwind_free(void);

enum {
    ACV_WHIRLWIND_HUFF      = 0,
    ACV_WHIRLWIND_BUZZAR    = 1,
};

#endif
