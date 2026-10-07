#pragma once

/// @file jan_14.h
/// @brief Jade Jungle - Deep Jungle 3

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

enum {
    NPC_JungleFuzzy_01  = 0,
    NPC_JungleFuzzy_02  = 1,
};

enum {
    MV_BushOffsetL      = MapVar(0),
    MV_BushOffsetR      = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupVines;
extern EvtScript EVS_SetupTrees;
extern NpcGroupList DefaultNPCs;
