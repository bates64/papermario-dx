#ifndef _UNUSED_FLEE_H_
#define _UNUSED_FLEE_H_

#include "common_structs.h"

// args: none
API_CALLABLE(InitActionCommand);

// args: prep time, duration, difficulty
API_CALLABLE(StartActionCommand);

void action_command_unused_flee_update(void);
void action_command_unused_flee_draw(void);
void action_command_unused_flee_free(void);

#endif
