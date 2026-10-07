#pragma once

/// @file mgm_00.h
/// @brief Minigame - Playroom Lobby

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mgm.h"
#include "map.xml.h"

#include "sprite/npc/Toad.h"

enum {
    NPC_RedToad         = 0,
    NPC_GreenToad       = 1,
    NPC_BlueToad        = 2,
};

enum {
    MV_RecordDisplayData        = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupScoreboard;
extern EvtScript EVS_BindInteractTriggers;
extern EvtScript EVS_OnEnterPipe_JumpAttack;
extern EvtScript EVS_OnEnterPipe_SmashAttack;
extern NpcGroupList DefaultNPCs;

void msg_draw_frame(s32 posX, s32 posY, s32 sizeX, s32 sizeY, s32 style, s32 palette, s32 fading, s32 bgAlpha, s32 frameAlpha);
