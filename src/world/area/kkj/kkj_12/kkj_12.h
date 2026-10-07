#pragma once

/// @file kkj_12.h
/// @brief Peach's Castle - Stairs Hallway (3F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "map.xml.h"

enum {
    NPC_Koopatrol_01    = 0,
    NPC_Koopatrol_02    = 1,
    NPC_Clubba          = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_ExitDoors_kkj_13_0;

extern NpcGroupList DefaultNPCs;
