#pragma once

/// @file kpa_96.h
/// @brief Bowser's Castle - Item Shop

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "mapfs/kpa_96_shape.h"
#include "mapfs/kpa_96_hit.h"

#include "sprite/npc/SpikedGoomba.h"

enum {
    NPC_SpikedGoomba    = 0,
};

enum {
    MV_MetShopkeeper    = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupShop;
extern NpcGroupList DefaultNPCs;
