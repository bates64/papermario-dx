#pragma once

/// @file pra_35.h
/// @brief Crystal Palace - Triple Dip Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    NPC_Clubba          = 0,
    NPC_Clubba_Hitbox   = 1,
    NPC_Duplighost      = 4,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
