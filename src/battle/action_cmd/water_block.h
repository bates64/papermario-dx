#pragma once

#include "common_structs.h"

API_CALLABLE(action_command_water_block_init);
API_CALLABLE(action_command_water_block_start);
void action_command_water_block_update(void);
void action_command_water_block_draw(void);
void action_command_water_block_free(void);
