#pragma once

/// @file dgb_16.h
/// @brief Tubba's Castle - Sleeping Clubbas Room (3F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

enum {
    NPC_Clubba_01               = 0,
    NPC_Clubba_01_Hitbox        = 1,
    NPC_Clubba_02               = 5,
    NPC_Clubba_02_Hitbox        = 6,
    NPC_Clubba_03               = 10,
    NPC_Clubba_03_Hitbox        = 11,
    NPC_Clubba_04               = 15,
    NPC_Clubba_04_Hitbox        = 16,
    NPC_Clubba_05               = 20,
    NPC_Clubba_05_Hitbox        = 21,
    NPC_Clubba_06               = 25,
    NPC_Clubba_06_Hitbox        = 26,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
