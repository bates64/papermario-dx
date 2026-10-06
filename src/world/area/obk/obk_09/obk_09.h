#pragma once

/// @file obk_09.h
/// @brief Boo's Mansion - Lady Bow's Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../obk.h"
#include "mapfs/obk_09_shape.h"
#include "mapfs/obk_09_hit.h"

#include "sprite/npc/WorldBow.h"
#include "sprite/npc/Bootler.h"
#include "sprite/npc/WorldSkolar.h"

enum {
    NPC_Bow                     = 0,
    NPC_Bootler                 = 1,
    NPC_Skolar                  = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayNewPartnerSong;
extern EvtScript EVS_ResetMusic;
extern EvtScript EVS_Scene_Epilogue;
extern EvtScript EVS_Scene_MeetBow;
extern NpcGroupList DefaultNPCs;
extern NpcGroupList EpilogueNPCs;
