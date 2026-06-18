#pragma once
#include "world/common/npc/GoombaFamily/base.h"
#include "sprite/npc/Goombaria.h"

#define GOOMBARIA_ANIMS \
{ \
    .idle   = ANIM_Goombaria_Idle, \
    .walk   = ANIM_Goombaria_Walk, \
    .run    = ANIM_Goombaria_Run, \
    .chase  = ANIM_Goombaria_Run, \
    .alert  = ANIM_Goombaria_Idle, \
    .unused = ANIM_Goombaria_Idle, \
    .death  = ANIM_Goombaria_Still, \
    .hit    = ANIM_Goombaria_Still, \
    .anim_8 = ANIM_Goombaria_Run, \
    .anim_9 = ANIM_Goombaria_Run, \
    .anim_A = ANIM_Goombaria_Run, \
    .anim_B = ANIM_Goombaria_Run, \
    .anim_C = ANIM_Goombaria_Run, \
    .anim_D = ANIM_Goombaria_Run, \
    .anim_E = ANIM_Goombaria_Run, \
    .anim_F = ANIM_Goombaria_Run, \
}
