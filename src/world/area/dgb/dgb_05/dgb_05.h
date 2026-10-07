#pragma once

/// @file dgb_05.h
/// @brief Tubba's Castle - Stairs Above Basement

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

enum {
    NPC_Clubba_01           = 0,
    NPC_Clubba_01_Hitbox    = 1,
    NPC_Clubba_02           = 3,
    NPC_Clubba_02_Hitbox    = 4,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupHole;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
