#pragma once

/// @file arn_07.h
/// @brief Gusty Gulch - Windmill Exterior

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "mapfs/arn_07_shape.h"
#include "mapfs/arn_07_hit.h"

#include "sprite/npc/TubbasHeart.h"
#include "sprite/npc/WorldTubba.h"
#include "sprite/npc/WorldBow.h"
#include "sprite/npc/Boo.h"
#include "sprite/npc/Bootler.h"

enum {
    NPC_TubbasHeart         = 0,
    NPC_Tubba               = 1,
    NPC_Boo_01              = 2,
    NPC_Boo_02              = 3,
    NPC_Boo_03              = 4,
    NPC_Boo_04              = 5,
    NPC_Boo_05              = 6,
    NPC_Boo_06              = 7,
    NPC_Bow                 = 8,
    NPC_Bootler             = 9,
    NPC_HyperParagoomba_01  = 10,
    NPC_HyperParagoomba_02  = 11,
    NPC_HyperParagoomba_03  = 12,
    NPC_Skolar              = 13,
};

enum {
    MV_EntityID_Padlock     = MapVar(0),
    MV_SpiritCardData       = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_UnlockDoor;
extern EvtScript EVS_SetupWindmill;
extern EvtScript EVS_SetupMusic;
extern EvtScript(EVS_SpawnStarCard);
extern EvtScript(EVS_ExitDoor_arn_08_0);

extern NpcGroupList DefaultNPCs;
extern NpcGroupList BossNPCs;
extern NpcGroupList SpiritNPCs;
