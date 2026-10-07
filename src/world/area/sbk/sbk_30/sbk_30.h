#pragma once

/// @file sbk_30.h
/// @brief Dry Dry Desert - W3 Kolorado's Camp

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sbk.h"
#include "map.xml.h"

#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/Kolorado.h"
#include "sprite/npc/WorldKooper.h"
#include "sprite/npc/Archeologist.h"

enum {
    NPC_Kolorado                = 0,
    NPC_Archeologist_01         = 1,
    NPC_Archeologist_02         = 2,
};

enum {
    MF_TreeDrop_Letter          = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFoliage;
extern NpcGroupList DefaultNPCs;
