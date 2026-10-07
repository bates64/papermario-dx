#pragma once

/// @file hos_10.h
/// @brief Shooting Star Summit - Ending Descent Scene

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "map.xml.h"

enum {
    NPC_Peach       = 0,
    NPC_Twink       = 1,
    NPC_Eldstar     = 2,
    NPC_Mamar       = 3,
    NPC_Skolar      = 4,
    NPC_Muskular    = 5,
    NPC_Misstar     = 6,
    NPC_Klevar      = 7,
    NPC_Kalmar      = 8,
};

enum {
    MV_BubbleFXPtr  = MapVar(0),
    MV_HaloFXPtr    = MapVar(1),
};

#include "sprite/player.h"

#include "world/common/npc/Dummy/idle.h"
#include "world/common/npc/Peach/base.h"
#include "world/common/npc/Twink/idle.h"
#include "world/common/npc/StarSpirit/idle.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Scene_CastleDescending;
extern EvtScript EVS_Scene_SpiritsFlyingAway;
extern EvtScript EVS_Scene_RisingAboveClouds;
extern EvtScript EVS_Scene_UnusedWhiteScreen;
extern EvtScript EVS_Scene_PreTitle;
#if VERSION_JP
extern EvtScript EVS_SetupNarrator;
#endif
extern NpcGroupList NpcGroup_Descent;
extern NpcGroupList NpcGroup_FlyAway;
