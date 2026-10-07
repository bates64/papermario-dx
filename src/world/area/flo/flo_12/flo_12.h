#pragma once

/// @file flo_12.h
/// @brief Flower Fields - (West) Rosie's Trellis

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "map.xml.h"

enum {
    NPC_Rosie       = 0,
    NPC_Dummy       = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushFlowerSong;
extern EvtScript EVS_PopMusic;
extern EvtScript EVS_Scene_SunReturns;
extern NpcGroupList DefaultNPCs;
