#pragma once

/// @file omo_11.h
/// @brief Shy Guy's Toybox - RED Moving Platforms

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "map.xml.h"

#include "sprite/npc/PyroGuy.h"

enum {
    NPC_PyroGuy_01      = 0,
    NPC_PyroGuy_02      = 1,
};

enum {
    MV_SuperBlock       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGizmos;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
