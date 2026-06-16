#pragma once
#include "npc.h"
#include "sprite/npc/Kolorado.h"

#define WHALE_ANIMS \
{ \
    .idle   = ANIM_Kolorado_Idle, \
    .walk   = ANIM_Kolorado_Walk, \
    .run    = ANIM_Kolorado_Run, \
    .chase  = ANIM_Kolorado_Run, \
    .alert  = ANIM_Kolorado_Idle, \
    .unused = ANIM_Kolorado_Idle, \
    .death  = ANIM_Kolorado_Idle, \
    .hit    = ANIM_Kolorado_Idle, \
    .anim_8 = ANIM_Kolorado_Idle, \
    .anim_9 = ANIM_Kolorado_Idle, \
    .anim_A = ANIM_Kolorado_Idle, \
    .anim_B = ANIM_Kolorado_Idle, \
    .anim_C = ANIM_Kolorado_Idle, \
    .anim_D = ANIM_Kolorado_Idle, \
    .anim_E = ANIM_Kolorado_Idle, \
    .anim_F = ANIM_Kolorado_Idle, \
}
