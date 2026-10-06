#pragma once

/// @file kkj_11.h
/// @brief Peach's Castle - Upper Hall (2F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "mapfs/kkj_11_shape.h"
#include "mapfs/kkj_11_hit.h"

enum {
    NPC_Koopatrol_01        = 0,
    NPC_Koopatrol_02        = 1,
    NPC_Koopatrol_03        = 2,
    NPC_Koopatrol_04        = 3,
    NPC_Koopatrol_05        = 4,
};

enum {
    MV_EntityID_Padlock     = MapVar(0),
};

#include "sprite/player.h"

#include "world/common/enemy/Koopatrol/idle.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_PlayDemoScene;
extern EvtScript EVS_FirstTimeEnterHall;
extern EvtScript EVS_ExitDoors_kkj_10_1;
extern EvtScript EVS_ExitDoors_kkj_12_0;
extern EvtScript EVS_ExitDoor_kkj_14_0;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList EarlyNPCs;
extern NpcGroupList LaterNPCs;

API_CALLABLE(CheckPlayerInSight);
API_CALLABLE(GetApproachPeachPos);
API_CALLABLE(UpdateSearchlight);
