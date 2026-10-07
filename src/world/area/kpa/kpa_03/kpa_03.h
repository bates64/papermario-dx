#pragma once

/// @file kpa_03.h
/// @brief Bowser's Castle - Dark Cave 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

#include "sprite/npc/BuzzyBeetle.h"
#include "sprite/npc/Magikoopa.h"
#include "sprite/npc/WorldKoopatrol.h"
#include "sprite/npc/BonyBeetle.h"

enum {
    NPC_Koopatrol_01            = 0,
    NPC_Koopatrol_02            = 1,
    NPC_BonyBeetle_01           = 2,
    NPC_BonyBeetle_02           = 3,
    NPC_Magikoopa_01            = 4,
    NPC_Magikoopa_01_Spell      = 5,
};

enum {
    MV_PlayerHeightLevel    = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
