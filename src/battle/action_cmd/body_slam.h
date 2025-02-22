#pragma once

#include "common_structs.h"

/// @evtapi
API_CALLABLE(action_command_body_slam_init);

/// @evtapi
/// @param prepTime
/// @param duration
/// @param difficulty
/// @param variation
API_CALLABLE(action_command_body_slam_start);

void action_command_body_slam_update(void);
void action_command_body_slam_draw(void);
void action_command_body_slam_free(void);

enum {
    ACV_SLAM_BOMBETTE   = 0,
    ACV_SLAM_WATT       = 1,
};
