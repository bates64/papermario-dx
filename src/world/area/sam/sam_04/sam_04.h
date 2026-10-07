#pragma once

/// @file sam_04.h
/// @brief Mt Shiver - Shiver Snowfield

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sam.h"
#include "map.xml.h"

#include "sprite/npc/Toad.h"
#include "sprite/npc/Penguin.h"

enum {
    NPC_Snowman_01      = 0,
    NPC_Snowman_02      = 1,
    NPC_Snowman_03      = 2,
    NPC_Snowman_04      = 3,
    NPC_Snowman_05      = 4,
    NPC_Snowman_06      = 5,
    NPC_LetterDummy     = 6,
};

enum {
    MV_LetterItemID     = MapVar(0),
    MV_DroppedLetter    = MapVar(1),
    MV_TreeHitCount     = MapVar(2),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupSnowmen;
extern EvtScript EVS_Scene_SnowmenSpeak;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
