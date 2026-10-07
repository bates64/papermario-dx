#pragma once

/// @file mim_10.h
/// @brief Forever Forest - Exit to Toad Town

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "map.xml.h"

#include "sprite/npc/Bootler.h"
#include "sprite/npc/JrTroopa.h"

enum {
    NPC_Bootler         = 0,
    NPC_JrTroopa        = 1,
};

enum {
    MV_ScenePlaying     = MapVar(0), // may be unread
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupBootlerTrigger;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
