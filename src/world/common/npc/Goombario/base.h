#pragma once
#include "world/common/npc/GoombaFamily/base.h"
#include "sprite/npc/WorldGoombario.h"

#define GOOMBARIO_ANIMS \
{ \
    .idle   = ANIM_WorldGoombario_Idle, \
    .walk   = ANIM_WorldGoombario_Walk, \
    .run    = ANIM_WorldGoombario_Run, \
    .chase  = ANIM_WorldGoombario_Run, \
    .alert  = ANIM_WorldGoombario_Idle, \
    .unused = ANIM_WorldGoombario_Idle, \
    .death  = ANIM_WorldGoombario_Still, \
    .hit    = ANIM_WorldGoombario_Still, \
    .anim_8 = ANIM_WorldGoombario_Run, \
    .anim_9 = ANIM_WorldGoombario_Run, \
    .anim_A = ANIM_WorldGoombario_Run, \
    .anim_B = ANIM_WorldGoombario_Run, \
    .anim_C = ANIM_WorldGoombario_Run, \
    .anim_D = ANIM_WorldGoombario_Run, \
    .anim_E = ANIM_WorldGoombario_Run, \
    .anim_F = ANIM_WorldGoombario_Run, \
}
