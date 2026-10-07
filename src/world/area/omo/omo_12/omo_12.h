#pragma once

/// @file omo_12.h
/// @brief Shy Guy's Toybox - RED Lantern Ghost

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "map.xml.h"

#include "sprite/npc/BigLanternGhost.h"
#include "sprite/npc/WorldWatt.h"

enum {
    NPC_BigLanternGhost     = 0,
    NPC_Watt                = 1,
    NPC_LaternTop           = 2,
    NPC_LaternBottom        = 3,
};

enum {
    MF_LanternGhost_DoneSpeaking    = MapFlag(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushPartnerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_SetupLightSource;
extern EvtScript EVS_EnterScene;
extern NpcGroupList DefaultNPCs;
