#pragma once

/// @file sbk_02.h
/// @brief Dry Dry Desert - N3W1 Ruins Entrance

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sbk.h"
#include "map.xml.h"

#include "sprite/npc/WorldMamar.h"
#include "sprite/npc/Toad.h"

enum {
    NPC_Mamar           = 1,
    NPC_TradingToad     = 2,
};

enum {
    MV_Effect_Sun       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupRuins;
extern EvtScript EVS_Ruins_Arise_Continued;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
