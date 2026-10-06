#pragma once

/// @file nok_04.h
/// @brief Koopa Region - Fuzzy Forest

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "mapfs/nok_04_shape.h"
#include "mapfs/nok_04_hit.h"

#include "sprite/npc/Fuzzy.h"
#include "sprite/npc/KooperWithoutShell.h"
#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/WorldKooper.h"

enum {
    NPC_BossFuzzy           = 0,
    NPC_KoopersShell        = 1,
    NPC_AmbushFuzzy         = 2,
    NPC_Fuzzy_01            = 3,
    NPC_Fuzzy_02            = 4,
    NPC_Fuzzy_03            = 5,
    NPC_Kooper              = 6,
};

enum {
    MV_CorrectCount         = MapVar(0),
    MV_CorrectTreeIndex     = MapVar(1),
    MV_WrongAnswerBattle    = MapVar(2),
    MV_LastWrongTreeIndex   = MapVar(3),
    MV_LastCorrectTreeIndex = MapVar(4), // unused
};

enum {
    TREE_0  = 0,
    TREE_1  = 1,
    TREE_2  = 2,
    TREE_3  = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushPartnerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_HitTree;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList DefaultNPCs;
