#pragma once

/// @file tik_02.h
/// @brief Toad Town Tunnels - Blooper Boss 1 (B1)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "map.xml.h"

enum {
    NPC_Blooper                 = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayBlooperSong;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupDrips;
extern NpcGroupList DefaultNPCs;
