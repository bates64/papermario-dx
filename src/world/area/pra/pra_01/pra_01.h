#pragma once

/// @file pra_01.h
/// @brief Crystal Palace - Entrance

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

#include "sprite/npc/WorldKalmar.h"

enum {
    NPC_Kalmar      = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
