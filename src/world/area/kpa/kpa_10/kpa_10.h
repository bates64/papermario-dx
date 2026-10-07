#pragma once

/// @file kpa_10.h
/// @brief Bowser's Castle - Outside Lower Jail (No Lava)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

#include "sprite/npc/Toad.h"
#include "sprite/npc/ToadGuard.h"

enum {
    NPC_Toad_01                 = 0,
    NPC_Toad_02                 = 1,
    NPC_ToadGuard               = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;
