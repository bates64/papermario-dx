#pragma once

/// @file kkj_19.h
/// @brief Peach's Castle - Kitchen (1F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kkj.h"
#include "map.xml.h"

#include "sprite/npc/TayceT.h"
#include "sprite/npc/Twink.h"

enum {
    // intro
    NPC_TayceT      = 0,
    NPC_Toad        = 1,
    // peach
    NPC_Twink       = 0, // normally, you cant interact with your partner, so a dummy npc is created to allow it
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ManageBaking;

extern NpcGroupList IntroNPCs;
extern NpcGroupList PeachNPCs;

extern IMG_BIN ui_box_corners5_png[];
