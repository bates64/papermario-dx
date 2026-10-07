#pragma once

/// @file isk_09.h
/// @brief Dry Dry Ruins - Super Hammer Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "map.xml.h"

enum {
    MF_BlueStairsFlipped    = MapFlag(0),
    MF_RedStairsFlipped     = MapFlag(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupSwitches;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayUpgradeSong;
extern EvtScript EVS_SetupStairs;
extern EvtScript EVS_MakeEntities;
