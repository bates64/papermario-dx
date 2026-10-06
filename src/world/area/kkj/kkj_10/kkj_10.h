#pragma once

/// @file kkj_10.h
/// @brief Peach's Castle - Entry Hall (1F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "mapfs/kkj_10_shape.h"
#include "mapfs/kkj_10_hit.h"

enum {
    NPC_Koopatrol_01    = 0,
    NPC_Koopatrol_02    = 1,
};

enum {
    MV_EntityID_Padlock = MapVar(0),
};

#include "sprite/player.h"

#include "world/common/enemy/Koopatrol/idle.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_ExitDoors_osr_02_1;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList EarlyNPCs;
extern NpcGroupList LaterNPCs;

API_CALLABLE(CheckPlayerInSight);
API_CALLABLE(GetApproachPeachPos);
API_CALLABLE(UpdateSearchlight);
