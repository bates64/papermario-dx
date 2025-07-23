#ifndef _DIZZY_SHELL_H_
#define _DIZZY_SHELL_H_

#include "common_structs.h"

// args: none
API_CALLABLE(InitActionCommand);

// args: prep time, duration, difficulty, chance
API_CALLABLE(StartActionCommand);

void action_command_dizzy_shell_update(void);
void action_command_dizzy_shell_draw(void);
void action_command_dizzy_shell_free(void);

#endif
