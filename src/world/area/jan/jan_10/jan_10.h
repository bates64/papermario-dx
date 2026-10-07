#pragma once

/// @file jan_10.h
/// @brief Jade Jungle - Western Dead End

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

enum {
    NPC_YoshiKid        = 0,
    NPC_JungleFuzzy     = 1,
};

enum {
    MF_KillLogShadow    = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupLogs;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_SetupBushes;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
