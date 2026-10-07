#pragma once

/// @file jan_16.h
/// @brief Jade Jungle - Base of Great Tree

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

#include "sprite/npc/Raven.h"
#include "sprite/npc/RaphaelRaven.h"

enum {
    NPC_RaphaelRaven    = 0,
    NPC_Raven_01        = 1,
    NPC_Raven_02        = 2,
    NPC_Raven_03        = 3,
    NPC_Raven_04        = 4,
    NPC_Raven_05        = 5,
};

enum {
    MV_BranchWobbleVel  = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupBushes;
extern EvtScript EVS_Scene_ReachedRaphaelsTree;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList DefaultNPCs;
