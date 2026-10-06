#pragma once

/// @file obk_05.h
/// @brief Boo's Mansion - Pot Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../obk.h"
#include "mapfs/obk_05_shape.h"
#include "mapfs/obk_05_hit.h"

#include "sprite/npc/Boo.h"

enum {
    NPC_Boo_01      = 0,
    NPC_Boo_02      = 1,
};

enum {
    MF_IsRetroMario     = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupRockingChairs;
extern EvtScript EVS_ManageHole;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;
