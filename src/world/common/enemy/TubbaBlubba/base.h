#pragma once
#include "npc.h"
#include "sprite/npc/WorldTubba.h"

#define TUBBA_ANIMS \
{ \
    .idle   = ANIM_WorldTubba_Anim06, \
    .walk   = ANIM_WorldTubba_Anim09, \
    .run    = ANIM_WorldTubba_Anim0C, \
    .chase  = ANIM_WorldTubba_Anim0C, \
    .alert  = ANIM_WorldTubba_Anim00, \
    .unused = ANIM_WorldTubba_Anim00, \
    .death  = ANIM_WorldTubba_Anim00, \
    .hit    = ANIM_WorldTubba_Anim00, \
    .anim_8 = ANIM_WorldTubba_Anim00, \
    .anim_9 = ANIM_WorldTubba_Anim00, \
    .anim_A = ANIM_WorldTubba_Anim00, \
    .anim_B = ANIM_WorldTubba_Anim00, \
    .anim_C = ANIM_WorldTubba_Anim00, \
    .anim_D = ANIM_WorldTubba_Anim00, \
    .anim_E = ANIM_WorldTubba_Anim00, \
    .anim_F = ANIM_WorldTubba_Anim00, \
}

#define TUBBA_ANGRY_ANIMS \
{ \
    .idle   = ANIM_WorldTubba_Anim07, \
    .walk   = ANIM_WorldTubba_Anim0A, \
    .run    = ANIM_WorldTubba_Anim0D, \
    .chase  = ANIM_WorldTubba_Anim0D, \
    .alert  = ANIM_WorldTubba_Anim19, \
    .unused = ANIM_WorldTubba_Anim07, \
    .death  = ANIM_WorldTubba_Anim07, \
    .hit    = ANIM_WorldTubba_Anim07, \
    .anim_8 = ANIM_WorldTubba_Anim07, \
    .anim_9 = ANIM_WorldTubba_Anim07, \
    .anim_A = ANIM_WorldTubba_Anim07, \
    .anim_B = ANIM_WorldTubba_Anim07, \
    .anim_C = ANIM_WorldTubba_Anim07, \
    .anim_D = ANIM_WorldTubba_Anim07, \
    .anim_E = ANIM_WorldTubba_Anim07, \
    .anim_F = ANIM_WorldTubba_Anim07, \
}

// same as CLUBBA_DROPS
#define TUBBA_DROPS \
{ \
    .dropFlags = NPC_DROP_FLAG_80, \
    .itemDropChance = 5, \
    .itemDrops = { \
        { ITEM_SUPER_SHROOM, 10, 0 }, \
    }, \
    .heartDrops  = STANDARD_HEART_DROPS(3), \
    .flowerDrops = STANDARD_FLOWER_DROPS(2), \
    .minCoinBonus = 2, \
    .maxCoinBonus = 3, \
}
