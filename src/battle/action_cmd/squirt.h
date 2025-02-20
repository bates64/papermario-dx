#pragma once

#include "common_structs.h"

API_CALLABLE(action_command_squirt_init);
API_CALLABLE(action_command_squirt_start);
void action_command_squirt_update(void);
void action_command_squirt_draw(void);
void action_command_squirt_free(void);
