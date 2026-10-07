#pragma once

/// @file kmr_06.h
/// @brief Goomba Region - Goomba Road 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

#include "sprite/npc/SpikedGoomba.h"
#include "sprite/npc/Paragoomba.h"

enum {
    NPC_SpikedGoomba            = 0,
    NPC_Paragoomba              = 1,
};

enum {
    MF_SignDroppedMushroom  = MapFlag(10),
};

enum {
    MV_StickerData          = MapVar(10),
    MV_StickerImage         = MapVar(11),
    MV_StickerPalette       = MapVar(12),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupStickerSign;
extern NpcGroupList DefaultNPCs;
