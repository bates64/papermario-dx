#pragma once

/// @file jan_06.h
/// @brief Jade Jungle - NE Jungle (Raven Statue)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

enum {
    NPC_JungleFuzzy         = 0,
    NPC_SpearGuy            = 1,
    NPC_SpearGuy_Hitbox     = 2,
    NPC_HeartPlant          = 3,
    NPC_HurtPlant_01        = 4,
    NPC_HurtPlant_02        = 5,
};

enum {
    MV_JadeRavenItemIdx = MapVar(11),
};

enum {
    MF_TreeDrop_Coin    = MapFlag(10),
    MF_KillLogShadow    = MapFlag(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupStatue;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_SetupBushes;
extern EvtScript EVS_SetupLogs;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList DefaultNPCs;
