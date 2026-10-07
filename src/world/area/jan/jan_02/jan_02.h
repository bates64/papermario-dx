#pragma once

/// @file jan_02.h
/// @brief Jade Jungle - Village Cove

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

#include "sprite/npc/WorldSushie.h"

enum {
    NPC_YoshiLeader         = 0,
    NPC_YoshiCouncillor     = 1,
    NPC_Yoshi_01            = 2,
    NPC_Yoshi_02            = 3,
    NPC_Yoshi_03            = 4,
    NPC_ChuckQuizmo         = 5,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFoliage;
extern NpcGroupList DefaultNPCs;
