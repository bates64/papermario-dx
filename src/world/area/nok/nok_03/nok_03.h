#pragma once

/// @file nok_03.h
/// @brief Koopa Region - Behind Koopa Village

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "map.xml.h"

#include "sprite/npc/WorldKooper.h"

enum {
    NPC_Fuzzy_01        = 0,
    NPC_Fuzzy_02        = 1,
    NPC_Fuzzy_03        = 4,
    NPC_KoopersShell    = 5,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
