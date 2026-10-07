#pragma once

/// @file osr_01.h
/// @brief Peach's Castle Grounds - Ruined Castle Grounds

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../osr.h"
#include "map.xml.h"

enum {
    NPC_Toad        = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlaySong_Starship;
extern EvtScript EVS_Scene_Wishing;
extern NpcGroupList DefaultNPCs;
