#pragma once

/// @file kmr_23.h
/// @brief Goomba Region - Chapter End

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "mapfs/kmr_23_shape.h"
#include "mapfs/kmr_23_hit.h"

#include "sprite/npc/WorldEldstar.h"
#include "sprite/npc/WorldMamar.h"
#include "sprite/npc/WorldSkolar.h"
#include "sprite/npc/WorldMuskular.h"
#include "sprite/npc/WorldMisstar.h"
#include "sprite/npc/WorldKlevar.h"
#include "sprite/npc/WorldKalmar.h"

enum {
    NPC_StarSpirit          = 0,
    NPC_AuxSpirit           = 1,
};

enum {
    MV_EndChapterDataPtr    = MapVar(0),
};

enum {
    MF_EndChapterSceneDone  = MapFlag(10),
    MF_SpiritReleased       = MapFlag(11),
};

extern EvtScript EVS_Main;
extern NpcGroupList NpcGroup_Eldstar;
extern NpcGroupList NpcGroup_Mamar;
extern NpcGroupList NpcGroup_Skolar;
extern NpcGroupList NpcGroup_Muskular;
extern NpcGroupList NpcGroup_Misstar;
extern NpcGroupList NpcGroup_Klevar;
extern NpcGroupList NpcGroup_Kalmar;
