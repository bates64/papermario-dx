#pragma once

/// @file hos_00.h
/// @brief Shooting Star Summit - Shooting Star Path

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "map.xml.h"

#include "sprite/npc/ToadKid.h"
#include "sprite/npc/Toadette.h"
#include "sprite/npc/Twink.h"
#include "sprite/npc/FlyingMagikoopa.h"
#include "sprite/npc/WorldGoombario.h"

enum {
    NPC_Twink                   = 0,
    NPC_FlyingMagikoopa         = 1,
    NPC_Toadette                = 2,
    NPC_ToadKid                 = 3,
};

enum {
    MV_LuckyStarItem        = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayKammyKoopaSong;
extern EvtScript EVS_Scene_MeetingTwink;
extern EvtScript EVS_Scene_TwinkDeparts;
extern EvtScript EVS_Scene_Wishing;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupBackgroundShade;
extern NpcGroupList DefaultNPCs;
extern NpcGroupList WishingNPCs;
