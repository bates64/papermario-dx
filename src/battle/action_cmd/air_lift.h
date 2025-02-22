#pragma once

#include "common_structs.h"

// args: chance of success
API_CALLABLE(action_command_air_lift_init);

// args: prep time, duration, difficulty, variation (unused)
API_CALLABLE(action_command_air_lift_start);

void action_command_air_lift_update(void);
void action_command_air_lift_draw(void);
void action_command_air_lift_free(void);
