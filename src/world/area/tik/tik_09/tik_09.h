#pragma once

/// @file tik_09.h
/// @brief Toad Town Tunnels - Warp Zone 2 (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "map.xml.h"

enum {
    NPC_KoopaTroopa_01          = 0,
    NPC_KoopaTroopa_02          = 1,
    NPC_KoopaTroopa_03          = 2,
};

enum {
    MV_EntityID_Switch          = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupDrips;
extern EvtScript EVS_SpawnSwitch;
extern NpcGroupList DefaultNPCs;
