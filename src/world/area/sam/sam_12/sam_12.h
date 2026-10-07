#pragma once

/// @file sam_12.h
/// @brief Mt Shiver - Merlar's Sanctuary

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sam.h"
#include "map.xml.h"

#include "sprite/npc/Merlar.h"

enum {
    NPC_Merlar  = 0,
};

enum {
    MV_StarStoneItemID  = MapVar(0),
};

enum {
    MF_DoneFadingIn     = MapFlag(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Scene_MeetMerlar;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
