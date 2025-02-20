#pragma once

#include <ultra64.h>
#include "common_structs.h"

#ifdef __cplusplus
extern "C" {
#endif

enum PlayerCollisionTests {
    PLAYER_COLLISION_0,
    PLAYER_COLLISION_1,
    PLAYER_COLLISION_2,
    PLAYER_COLLISION_HAMMER,
    PLAYER_COLLISION_4,
};

HitID player_raycast_below_cam_relative(PlayerStatus* playerStatus, f32* outX, f32* outY, f32* outZ, f32* outLength,
                                        f32* hitRx, f32* hitRz, f32* hitDirX, f32* hitDirZ);

HitID player_raycast_up_corners(PlayerStatus* player, f32* posX, f32* posY, f32* posZ, f32* hitDepth, f32 yaw);

HitID player_test_lateral_overlap(enum PlayerCollisionTests mode, PlayerStatus* playerStatus, f32* x, f32* y, f32* z, f32 length, f32 yaw);

HitID player_test_move_with_slipping(PlayerStatus* playerStatus, f32* x, f32* y, f32* z, f32 length, f32 yaw);

/// Only used for Peach physics.
HitID player_test_move_without_slipping(PlayerStatus* playerStatus, f32* x, f32* y, f32* z, f32 length, f32 yaw, s32* hasClimbableStep);

#ifdef __cplusplus
}
#endif
