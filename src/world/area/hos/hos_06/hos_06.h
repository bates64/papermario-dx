#pragma once

/// @file hos_06.h
/// @brief Shooting Star Summit - Merluvlee's House

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "mapfs/hos_06_shape.h"
#include "mapfs/hos_06_hit.h"

#include "sprite/npc/Merlow.h"
#include "sprite/npc/Merluvlee.h"

#define MERLOW_BADGE_COUNT 15

enum {
    NPC_Merluvlee   = 0,
    NPC_Merlow      = 1,
};

enum {
    MV_RitualFXArrayPtr = MapVar(10),
};

enum {
    MF_PurchasedBadge   = MapFlag(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMagicChest;
extern EvtScript EVS_Interact_MagicChest;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_AskForHint;

extern EvtScript EVS_NpcInteract_Merluvlee;
extern EvtScript EVS_NpcInit_Merluvlee;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
