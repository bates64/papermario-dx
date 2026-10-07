#pragma once

/// @file kmr_12.h
/// @brief Goomba Region - Goomba Road 4

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

#include "sprite/npc/Goomba.h"

enum {
    NPC_Goomba_Ambush   = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_OnReadBillboard;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
