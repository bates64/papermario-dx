#pragma once

/// @file isk_04.h
/// @brief Dry Dry Ruins - Descending Stairs 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "map.xml.h"

#include "sprite/npc/BuzzyBeetle.h"

enum {
    NPC_BuzzyBeetle_01          = 0,
    NPC_BuzzyBeetle_02          = 1,
};

enum {
    MV_RuinsLockEntityID        = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupObstructions;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupDemo;
extern NpcGroupList DefaultNPCs;
