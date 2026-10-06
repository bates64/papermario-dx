#pragma once

/// @file obk_02.h
/// @brief Boo's Mansion - Basement Stairs

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../obk.h"
#include "mapfs/obk_02_shape.h"
#include "mapfs/obk_02_hit.h"

#include "sprite/npc/Boo.h"

enum {
    NPC_TrafficBoo1     = 0,
    NPC_TrafficBoo2     = 1,
};

enum {
    MV_CurrentMapRegion     = MapVar(0),
    MV_LastMapRegion        = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_UpdateClock;
extern EvtScript EVS_ClockDoNothing;
extern EvtScript EVS_SetupBombableWall;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;
