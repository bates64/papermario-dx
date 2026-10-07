#pragma once

/// @file kzn_19.h
/// @brief Mt Lavalava - Boss Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    NPC_Kolorado                = 0,
    NPC_Misstar                 = 1,
    NPC_LavaPiranhaHead         = 2,
    NPC_LavaBud_01              = 3,
    NPC_LavaBud_02              = 4,
    NPC_05                      = 5,
};

enum {
    MV_VinesData                = MapVar(0),
    MV_SpiritCardData           = MapVar(1),
    MV_BossDefeated             = MapVar(10),
};

extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_UpdateEruption;
extern EvtScript EVS_Misstar_Escape;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList BossNPCs;
extern NpcGroupList EscapeNPCs;

extern EvtScript EVS_TrySpawningStarCard;
extern StaticAnimatorNode* AnimModel_MainHeadVine[];
extern StaticAnimatorNode* AnimModel_SideHeadVine[];
extern StaticAnimatorNode* AnimModel_ExtraVine[];

#include "world/common/npc/Kolorado/idle.h"
#include "world/common/npc/StarSpirit/idle.h"
#include "world/common/enemy/LavaPiranha/idle.h"

extern API_CALLABLE(SetAnimatorFlags);
extern API_CALLABLE(GetAnimatedPositionByTreeIndex);
extern API_CALLABLE(GetAnimatedRotationByTreeIndex);
