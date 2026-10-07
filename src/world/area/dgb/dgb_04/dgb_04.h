#pragma once

/// @file dgb_04.h
/// @brief Tubba's Castle - Stairs to Basement

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

enum {
    NPC_Sentinel    = 0,
};

enum {
    MV_SuperBlock   = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
