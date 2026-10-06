#pragma once

/// @file kzn_02.h
/// @brief Mt Lavalava - First Lava Lake

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "mapfs/kzn_02_shape.h"
#include "mapfs/kzn_02_hit.h"

enum {
    NPC_Kolorado                = 0,
    NPC_LavaBubble              = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_InitializePlatforms;
extern EvtScript EVS_PlayDemoScene;
extern EvtScript EVS_KoloradoSinkingPlatform;
extern NpcGroupList DefaultNPCs;
