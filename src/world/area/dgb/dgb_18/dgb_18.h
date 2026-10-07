#pragma once

/// @file dgb_18.h
/// @brief Tubba's Castle - Master Bedroom (3F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

#include "sprite/npc/WorldTubba.h"
#include "sprite/npc/Yakkey.h"
#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/WorldKooper.h"
#include "sprite/npc/WorldBombette.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/WorldBow.h"

enum {
    NPC_Tubba                   = 0,
    NPC_Yakkey                  = 1,
};

enum {
    MF_Sync_YakkeyDialogue      = MapFlag(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
