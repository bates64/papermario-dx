#pragma once

/// @file kkj_02.h
/// @brief Peach's Castle - Intro Stairs Hallway (3F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "map.xml.h"

enum {
    NPC_Toad            = 0,
    NPC_ToadGuard       = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
