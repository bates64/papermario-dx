#pragma once

/// @file pra_13.h
/// @brief Crystal Palace - Blue Mirror Hall 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

#include "sprite/npc/WorldBombette.h"
#include "sprite/npc/Duplighost.h"

enum {
    NPC_FakeMario           = 0,
    NPC_FakeBombette        = 1,
    NPC_Duplighost_01       = 2,
    NPC_Duplighost_02       = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
