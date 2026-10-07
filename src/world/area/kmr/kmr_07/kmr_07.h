#pragma once

/// @file kmr_07.h
/// @brief Goomba Region - Goomba Road 3

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

enum {
    NPC_GoombaBros_Red          = 0,
    NPC_GoombaBros_Blue         = 1,
};

enum {
    MV_EntityID_Spring          = MapVar(0),
    MV_GoombaBrosDefeated       = MapVar(0), // reused
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
