#pragma once

/// @file flo_09.h
/// @brief Flower Fields - (East) Triple Tree Path

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "map.xml.h"

#include "sprite/npc/Dayzee.h"
#include "sprite/npc/Bzzap.h"

enum {
    NPC_Dayzee_01               = 0,
    NPC_Dayzee_02               = 1,
    NPC_Bzzap_01                = 2,
    NPC_Bzzap_02                = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_SetupVines;
extern NpcGroupList DefaultNPCs;
