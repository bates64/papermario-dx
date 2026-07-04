#pragma once
#include "npc.h"
#include "sprite/npc/Archeologist.h"

#define ARCHEOLOGIST_ANIMS \
{ \
    .idle   = ANIM_Archeologist_Idle, \
    .walk   = ANIM_Archeologist_Walk, \
    .run    = ANIM_Archeologist_Run, \
    .chase  = ANIM_Archeologist_Run, \
    .alert  = ANIM_Archeologist_Idle, \
    .unused = ANIM_Archeologist_Idle, \
    .death  = ANIM_Archeologist_Idle, \
    .hit    = ANIM_Archeologist_Idle, \
    .anim_8 = ANIM_Archeologist_Idle, \
    .anim_9 = ANIM_Archeologist_Idle, \
    .anim_A = ANIM_Archeologist_Idle, \
    .anim_B = ANIM_Archeologist_Idle, \
    .anim_C = ANIM_Archeologist_Idle, \
    .anim_D = ANIM_Archeologist_Idle, \
    .anim_E = ANIM_Archeologist_Idle, \
    .anim_F = ANIM_Archeologist_Idle, \
}
