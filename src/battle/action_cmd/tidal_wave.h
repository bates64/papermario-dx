#pragma once

#include "common_structs.h"

API_CALLABLE(action_command_tidal_wave_init);
API_CALLABLE(action_command_tidal_wave_start);
void action_command_tidal_wave_update(void);
void action_command_tidal_wave_draw(void);
void action_command_tidal_wave_free(void);
