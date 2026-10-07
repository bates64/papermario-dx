#pragma once

/// @file kkj_20.h
/// @brief Peach's Castle - Guest Room (1F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "map.xml.h"

#include "sprite/npc/Toad.h"
#include "sprite/npc/Twink.h"

enum {
    NPC_Toad    = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_PlayBowserSong;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList DefaultNPCs;
