#ifndef _HURRICANE_H_
#define _HURRICANE_H_

#include "common_structs.h"

// args: none
API_CALLABLE(InitActionCommand);

// args: prep time, duration, difficulty, chance
API_CALLABLE(StartActionCommand);

void action_command_hurricane_update(void);
void action_command_hurricane_draw(void);
void action_command_hurricane_free(void);

#endif
