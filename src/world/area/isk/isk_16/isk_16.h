#pragma once

/// @file isk_16.h
/// @brief Dry Dry Ruins - Tutankoopa Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "map.xml.h"

#include "sprite/npc/Tutankoopa.h"
#include "sprite/npc/ChainChomp.h"

enum {
    NPC_Tutankoopa_01       = 0,
    NPC_Tutankoopa_02       = 1,
    NPC_ChainChomp          = 2,
};

enum {
    MV_SpiritCardData       = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFlames;
extern EvtScript EVS_SpawnStarCard;
extern EvtScript EVS_Scene_TutankoopaDefeated;
extern EvtScript EVS_Scene_TutankoopaAppears;
extern EvtScript EVS_BindExitTriggers;
extern NpcGroupList DefaultNPCs;
