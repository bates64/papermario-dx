#pragma once
#include "world/common/npc/GoombaFamily/base.h"
#include "sprite/npc/Goomama.h"

#define GOOMAMA_ANIMS \
{ \
    .idle   = ANIM_Goomama_Idle, \
    .walk   = ANIM_Goomama_Walk, \
    .run    = ANIM_Goomama_Run, \
    .chase  = ANIM_Goomama_Run, \
    .alert  = ANIM_Goomama_Idle, \
    .unused = ANIM_Goomama_Idle, \
    .death  = ANIM_Goomama_Still, \
    .hit    = ANIM_Goomama_Still, \
    .anim_8 = ANIM_Goomama_Run, \
    .anim_9 = ANIM_Goomama_Run, \
    .anim_A = ANIM_Goomama_Run, \
    .anim_B = ANIM_Goomama_Run, \
    .anim_C = ANIM_Goomama_Run, \
    .anim_D = ANIM_Goomama_Run, \
    .anim_E = ANIM_Goomama_Run, \
    .anim_F = ANIM_Goomama_Run, \
}
