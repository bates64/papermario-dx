#pragma once
#include "world/common/npc/GoombaFamily/base.h"
#include "sprite/npc/Goompapa.h"

#define GOOMPAPA_ANIMS \
{ \
    .idle   = ANIM_Goompapa_Idle, \
    .walk   = ANIM_Goompapa_Walk, \
    .run    = ANIM_Goompapa_Run, \
    .chase  = ANIM_Goompapa_Run, \
    .alert  = ANIM_Goompapa_Idle, \
    .unused = ANIM_Goompapa_Idle, \
    .death  = ANIM_Goompapa_Still, \
    .hit    = ANIM_Goompapa_Still, \
    .anim_8 = ANIM_Goompapa_Run, \
    .anim_9 = ANIM_Goompapa_Run, \
    .anim_A = ANIM_Goompapa_Run, \
    .anim_B = ANIM_Goompapa_Run, \
    .anim_C = ANIM_Goompapa_Run, \
    .anim_D = ANIM_Goompapa_Run, \
    .anim_E = ANIM_Goompapa_Run, \
    .anim_F = ANIM_Goompapa_Run, \
}
