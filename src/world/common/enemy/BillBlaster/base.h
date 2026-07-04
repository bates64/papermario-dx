#pragma once
#include "npc.h"
#include "sprite/npc/BillBlaster.h"

#define BILL_BLASTER_DROPS \
{ \
    .dropFlags = NPC_DROP_FLAG_80, \
    .heartDrops  = STANDARD_HEART_DROPS(2), \
    .flowerDrops = STANDARD_FLOWER_DROPS(2), \
    .minCoinBonus = 1, \
    .maxCoinBonus = 1, \
}

#define BILL_BLASTER_ANIMS \
{ \
    .idle   = ANIM_BillBlaster_Idle, \
    .walk   = ANIM_BillBlaster_Idle, \
    .run    = ANIM_BillBlaster_Idle, \
    .chase  = ANIM_BillBlaster_Idle, \
    .alert  = ANIM_BillBlaster_Idle, \
    .unused = ANIM_BillBlaster_Idle, \
    .death  = ANIM_BillBlaster_Hurt, \
    .hit    = ANIM_BillBlaster_Hurt, \
    .anim_8 = ANIM_BillBlaster_Idle, \
    .anim_9 = ANIM_BillBlaster_Idle, \
    .anim_A = ANIM_BillBlaster_Idle, \
    .anim_B = ANIM_BillBlaster_Idle, \
    .anim_C = ANIM_BillBlaster_Idle, \
    .anim_D = ANIM_BillBlaster_Idle, \
    .anim_E = ANIM_BillBlaster_Idle, \
    .anim_F = ANIM_BillBlaster_Idle, \
}
