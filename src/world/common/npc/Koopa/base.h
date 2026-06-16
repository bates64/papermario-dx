#pragma once
#include "npc.h"
#include "sprite/npc/Koopa.h"

#define KOOPA_ANIMS \
{ \
    .idle   = ANIM_Koopa_Idle, \
    .walk   = ANIM_Koopa_Walk, \
    .run    = ANIM_Koopa_Run, \
    .chase  = ANIM_Koopa_Run, \
    .alert  = ANIM_Koopa_Idle, \
    .unused = ANIM_Koopa_Idle, \
    .death  = ANIM_Koopa_Still, \
    .hit    = ANIM_Koopa_Still, \
    .anim_8 = ANIM_Koopa_Still, \
    .anim_9 = ANIM_Koopa_Still, \
    .anim_A = ANIM_Koopa_Still, \
    .anim_B = ANIM_Koopa_Still, \
    .anim_C = ANIM_Koopa_Still, \
    .anim_D = ANIM_Koopa_Still, \
    .anim_E = ANIM_Koopa_Still, \
    .anim_F = ANIM_Koopa_Still, \
}
