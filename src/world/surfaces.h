#pragma once

#include "common.h"

enum SurfaceWalkEffect {
    SURFACE_WALK_FX_STANDARD,   // puffs of dust follow the player
    SURFACE_WALK_FX_SPARKLE,    // trail of sparkles follow the player, only used in hos_02 in vanilla
};

void player_surface_spawn_fx(void);

/// Select the type of surface effect spawned by the player while moving
/// The effect is reset between maps, so include this in the Main script for every map you wish to change.
/// @param type enum value from SurfaceWalkEffect
void surface_set_walk_effect(s32 effect);

/// Select the type of surface effect spawned by the player while moving
/// The effect is reset between maps, so include this in the Main script for every map you wish to change.
/// @param type enum value from SurfaceWalkEffect
/// @evtapi
API_CALLABLE(SetSurfaceWalkEffect);
