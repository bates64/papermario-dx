#pragma once
#include "world/common/npc/GoombaFamily/base.h"
#include "sprite/npc/Goompa.h"

#define GOOMPA_ANIMS \
{ \
    .idle   = ANIM_Goompa_Idle, \
    .walk   = ANIM_Goompa_Walk, \
    .run    = ANIM_Goompa_Run, \
    .chase  = ANIM_Goompa_Run, \
    .alert  = ANIM_Goompa_Idle, \
    .unused = ANIM_Goompa_Idle, \
    .death  = ANIM_Goompa_Still, \
    .hit    = ANIM_Goompa_Still, \
    .anim_8 = ANIM_Goompa_Run, \
    .anim_9 = ANIM_Goompa_Run, \
    .anim_A = ANIM_Goompa_Run, \
    .anim_B = ANIM_Goompa_Run, \
    .anim_C = ANIM_Goompa_Run, \
    .anim_D = ANIM_Goompa_Run, \
    .anim_E = ANIM_Goompa_Run, \
    .anim_F = ANIM_Goompa_Run, \
}
