#pragma once

/// @file sbk_00.h
/// @brief Dry Dry Desert - N3W3

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sbk.h"
#include "map.xml.h"

#include "sprite/npc/Pokey.h"

enum {
    NPC_Pokey_01                = 0,
    NPC_Pokey_02                = 1,
};

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;
