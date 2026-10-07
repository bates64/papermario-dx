#pragma once

/// @file flo_22.h
/// @brief Flower Fields - (East) Old Well

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "map.xml.h"

#include "sprite/npc/Bzzap.h"
#include "sprite/npc/Dayzee.h"

enum {
    NPC_Dummy   = 0, // reused as a dummy for tossing badge out of the well
    NPC_Bzzap   = 0,
    NPC_Dayzee  = 1,
};

enum {
    MV_Bzzap_State      = MapVar(10),
    MV_Dayzee_State     = MapVar(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_SetupWell;
extern EvtScript EVS_SniffleHint;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
