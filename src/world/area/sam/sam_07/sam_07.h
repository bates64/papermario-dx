#pragma once

/// @file sam_07.h
/// @brief Mt Shiver - Shiver Mountain Passage

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sam.h"
#include "map.xml.h"

#include "sprite/npc/Gulpit.h"
#include "sprite/npc/LargePiranha.h"

enum {
    NPC_Gulpit                  = 0,
    NPC_Gulpit_Hitbox           = 1,
    NPC_FrostPiranha_01         = 2,
    NPC_FrostPiranha_01_Hitbox  = 3,
    NPC_FrostPiranha_02         = 4,
    NPC_FrostPiranha_02_Hitbox  = 5,
};

enum {
    MV_SwitchEntityID       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupPit;
extern EvtScript EVS_UseGreenSwitch;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
