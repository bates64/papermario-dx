#pragma once

/// @file kpa_17.h
/// @brief Bowser's Castle - Lower Jail

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

#include "sprite/npc/WorldBombette.h"
#include "sprite/npc/Toad.h"

enum {
    NPC_Toad_01                 = 0,
    NPC_Toad_02                 = 1,
    NPC_ToadGuard               = 2,
    NPC_ToadMinister            = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_BlastWall;
extern EvtScript EVS_Scene_FallIntoCell;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
