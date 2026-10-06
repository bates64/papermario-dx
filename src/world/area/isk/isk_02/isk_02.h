#pragma once

/// @file isk_02.h
/// @brief Dry Dry Ruins - Sarcophagus Hall 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "mapfs/isk_02_shape.h"
#include "mapfs/isk_02_hit.h"

#include "sprite/npc/Pokey.h"

enum {
    NPC_Pokey_01                = 0,
    NPC_Pokey_02                = 1,
    NPC_Pokey_03                = 2,
};

enum {
    MV_EntityID_Padlock         = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupLock;
extern EvtScript EVS_SetupSarcophagi;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
