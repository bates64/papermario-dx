#pragma once

/// @file kkj_03.h
/// @brief Peach's Castle - Intro Window Hallway (4F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "mapfs/kkj_03_shape.h"
#include "mapfs/kkj_03_hit.h"

enum {
    NPC_Peach   = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Scene_MeetingPeach;
extern EvtScript EVS_Scene_Ascending;

extern NpcGroupList DefaultNPCs;
