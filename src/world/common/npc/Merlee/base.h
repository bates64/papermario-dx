#pragma once
#include "npc.h"
#include "sprite/npc/WorldMerlee.h"

#define MERLEE_ANIMS \
{ \
    .idle   = ANIM_WorldMerlee_Idle, \
    .walk   = ANIM_WorldMerlee_Walk, \
    .run    = ANIM_WorldMerlee_Run, \
    .chase  = ANIM_WorldMerlee_Run, \
    .alert  = ANIM_WorldMerlee_Idle, \
    .unused = ANIM_WorldMerlee_Idle, \
    .death  = ANIM_WorldMerlee_Idle, \
    .hit    = ANIM_WorldMerlee_Idle, \
    .anim_8 = ANIM_WorldMerlee_Idle, \
    .anim_9 = ANIM_WorldMerlee_Idle, \
    .anim_A = ANIM_WorldMerlee_Idle, \
    .anim_B = ANIM_WorldMerlee_Idle, \
    .anim_C = ANIM_WorldMerlee_Idle, \
    .anim_D = ANIM_WorldMerlee_Idle, \
    .anim_E = ANIM_WorldMerlee_Idle, \
    .anim_F = ANIM_WorldMerlee_Idle, \
}
