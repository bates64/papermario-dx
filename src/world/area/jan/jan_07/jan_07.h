#pragma once

/// @file jan_07.h
/// @brief Jade Jungle - Small Jungle Ledge

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

enum {
    NPC_YoshiKid                = 0,
    NPC_PutridPiranha_01        = 1,
    NPC_PutridPiranha_02        = 2,
    NPC_SpearGuy                = 10,
    NPC_SpearGuy_Hitbox         = 11,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_SetupBushes;
extern NpcGroupList DefaultNPCs;
