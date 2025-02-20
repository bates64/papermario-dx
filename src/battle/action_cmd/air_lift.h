#pragma once

#include "common_structs.h"

API_CALLABLE(action_command_air_lift_init);
API_CALLABLE(action_command_air_lift_start);
void action_command_air_lift_update(void);
void action_command_air_lift_draw(void);
void action_command_air_lift_free(void);
