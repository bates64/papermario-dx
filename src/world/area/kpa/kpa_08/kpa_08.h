#pragma once

/// @file kpa_08.h
/// @brief Bowser's Castle - Castle Key Timing Puzzle

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

#include "sprite/npc/Magikoopa.h"

enum {
    NPC_Magikoopa           = 0,
    NPC_Magikoopa_Spell     = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
