#pragma once

/// @file isk_07.h
/// @brief Dry Dry Ruins - Sarcophagus Hall 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "mapfs/isk_07_shape.h"
#include "mapfs/isk_07_hit.h"

#include "sprite/npc/Pokey.h"

enum {
    NPC_Pokey_01                = 0,
    NPC_Pokey_02                = 1,
    NPC_Pokey_03                = 2,
};

enum {
    MV_LockEntityID         = MapVar(0),
};

enum {
    MF_StairsFlipped        = MapFlag(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupLock;
extern EvtScript EVS_SetupStairs;
extern EvtScript EVS_SetupSwitch;
extern EvtScript EVS_SetupSarcophagi;
extern EvtScript EVS_OpenEntryDoor;
extern EvtScript EVS_ShutEntryDoor;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
