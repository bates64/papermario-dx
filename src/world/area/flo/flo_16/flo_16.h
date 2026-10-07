#pragma once

/// @file flo_16.h
/// @brief Flower Fields - (NE) Elevators

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "map.xml.h"

#include "sprite/npc/RuffPuff.h"

enum {
    NPC_RuffPuff_01     = 0,
    NPC_RuffPuff_02     = 1,
};

enum {
    MV_SuperBlock       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupVines;
extern EvtScript EVS_SetupPillarPuzzle;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList DefaultNPCs;
