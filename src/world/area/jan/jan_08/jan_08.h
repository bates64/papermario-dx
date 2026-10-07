#pragma once

/// @file jan_08.h
/// @brief Jade Jungle - SW Jungle (Super Block)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

enum {
    NPC_SpearGuy            = 0,
    NPC_SpearGuy_Hitbox     = 1,
    NPC_HurtPlant           = 2,
    NPC_MBush_01            = 3,
    NPC_MBush_02            = 4,
    NPC_HeartPlant_01       = 5,
    NPC_HeartPlant_02       = 6,
    NPC_YoshiKid            = 7,
};

enum {
    MV_BushMoveL        = MapVar(0),
    MV_BushMoveR        = MapVar(1),
    MV_SuperBlock       = MapVar(2),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupBushes;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
