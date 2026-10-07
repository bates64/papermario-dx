#pragma once

/// @file jan_11.h
/// @brief Jade Jungle - Root Cavern

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

#include "sprite/npc/YoshiKid.h"

enum {
    NPC_YoshiKid    = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
