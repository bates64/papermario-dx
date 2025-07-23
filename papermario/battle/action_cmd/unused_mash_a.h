#ifndef _UNUSED_MASH_A_H_
#define _UNUSED_MASH_A_H_

#include "common_structs.h"

// args: none
API_CALLABLE(InitActionCommand);

// args: prep time, duration, difficulty
API_CALLABLE(StartActionCommand);

void action_command_unused_mash_a_update(void);
void action_command_unused_mash_a_draw(void);
void action_command_unused_mash_a_free(void);

#endif
