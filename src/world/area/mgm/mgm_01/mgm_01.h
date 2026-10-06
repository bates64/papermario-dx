#pragma once

/// @file mgm_01.h
/// @brief Minigame - Jump Attack Minigame

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mgm.h"
#include "mapfs/mgm_01_shape.h"
#include "mapfs/mgm_01_hit.h"

#include "sprite/npc/Toad.h"

enum {
    NPC_Toad                    = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_802424A4;
extern NpcGroupList DefaultNPCs;

API_CALLABLE(SetMsgImgs_Panels);

void delete_entity(s32 entityIndex);
