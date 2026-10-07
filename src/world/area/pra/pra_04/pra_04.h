#pragma once

/// @file pra_04.h
/// @brief Crystal Palace - Reflected Save Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    NPC_Swoopula    = 0,
};

enum {
    MV_PlayerFloor  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
