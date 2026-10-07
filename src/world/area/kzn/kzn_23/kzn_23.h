#pragma once

/// @file kzn_23.h
/// @brief Mt Lavalava - Volcano Escape

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    NPC_Kolorado    = 0,
    NPC_Misstar     = 1,
};

enum {
    MV_LavaLevel    = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
