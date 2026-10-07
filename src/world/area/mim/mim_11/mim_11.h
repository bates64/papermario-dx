#pragma once

/// @file mim_11.h
/// @brief Forever Forest - Outside Boo's Mansion

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "map.xml.h"

#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/WorldKooper.h"
#include "sprite/npc/WorldBombette.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/Bootler.h"
#include "sprite/npc/WorldSkolar.h"

enum {
    NPC_Bootler         = 0,
    NPC_Skolar          = 2,
};

enum {
    MF_Drop_Bush1       = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupMansionGate;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_SetupMusic;

extern NpcGroupList DefaultNPCs;
