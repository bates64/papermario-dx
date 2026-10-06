#pragma once

/// @file tik_08.h
/// @brief Toad Town Tunnels - Second Level Entry (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_08_shape.h"
#include "mapfs/tik_08_hit.h"

enum {
    NPC_Blooper                 = 0,
};

enum {
    MV_BlueSwitch       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayBlooperSong;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SpawnSwitch;
extern EvtScript EVS_SetupDrips;
extern NpcGroupList DefaultNPCs;
