#pragma once

/// @file kpa_113.h
/// @brief Bowser's Castle - Room with Hidden Door 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

enum {
    NPC_BonyBeetle      = 0,
};

enum {
    MV_EntityID_Padlock  = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupStatues;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
