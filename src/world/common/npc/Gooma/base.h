#pragma once
#include "world/common/npc/GoombaFamily/base.h"
#include "sprite/npc/Gooma.h"

#define GOOMA_ANIMS \
{ \
    .idle   = ANIM_Gooma_Idle, \
    .walk   = ANIM_Gooma_Walk, \
    .run    = ANIM_Gooma_Run, \
    .chase  = ANIM_Gooma_Run, \
    .alert  = ANIM_Gooma_Idle, \
    .unused = ANIM_Gooma_Idle, \
    .death  = ANIM_Gooma_Still, \
    .hit    = ANIM_Gooma_Still, \
    .anim_8 = ANIM_Gooma_Run, \
    .anim_9 = ANIM_Gooma_Run, \
    .anim_A = ANIM_Gooma_Run, \
    .anim_B = ANIM_Gooma_Run, \
    .anim_C = ANIM_Gooma_Run, \
    .anim_D = ANIM_Gooma_Run, \
    .anim_E = ANIM_Gooma_Run, \
    .anim_F = ANIM_Gooma_Run, \
}
