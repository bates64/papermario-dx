#pragma once

/// @file dgb_02.h
/// @brief Tubba's Castle - West Hall (1F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

enum {
    NPC_Clubba_01           = 10,
    NPC_Clubba_01_Hitbox    = 11,
    NPC_Clubba_02           = 30,
    NPC_Clubba_02_Hitbox    = 31,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
