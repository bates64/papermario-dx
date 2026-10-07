#pragma once

/// @file arn_03.h
/// @brief Gusty Gulch - Ghost Town 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "map.xml.h"

#include "sprite/npc/Boo.h"
#include "sprite/npc/WorldBow.h"

enum {
    NPC_Boo_01          = 0,
    NPC_Boo_02          = 1,
    NPC_Boo_03          = 2,
    NPC_Boo_04          = 3,
    NPC_Boo_Prankster   = 4,
    NPC_Boo_06          = 5,
    NPC_Boo_07          = 6,
    NPC_Boo_08          = 7,
    NPC_Boo_09          = 8,
};

enum {
    MV_Koot_Time        = MapVar(0),
    MV_Koot_WaitLength  = MapVar(1),
    MV_PrankDone        = MapVar(2),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList BeforeNPCs;
extern NpcGroupList AfterNPCs;
