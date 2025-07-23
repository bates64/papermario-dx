#ifndef _AIR_LIFT_H_
#define _AIR_LIFT_H_

#include "common_structs.h"

// args: chance of success
API_CALLABLE(InitActionCommand);

// args: prep time, duration, difficulty, variation (unused)
API_CALLABLE(StartActionCommand);

void action_command_air_lift_update(void);
void action_command_air_lift_draw(void);
void action_command_air_lift_free(void);

#endif
