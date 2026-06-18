#pragma once
#include "npc.h"
#include "sprite/npc/ChuckQuizmo.h"

#define QUIZMO_ANIMS \
{ \
    .idle   = ANIM_ChuckQuizmo_Idle, \
    .walk   = ANIM_ChuckQuizmo_Walk, \
    .run    = ANIM_ChuckQuizmo_Run, \
    .chase  = ANIM_ChuckQuizmo_Run, \
    .alert  = ANIM_ChuckQuizmo_Idle, \
    .unused = ANIM_ChuckQuizmo_Idle, \
    .death  = ANIM_ChuckQuizmo_Still, \
    .hit    = ANIM_ChuckQuizmo_Still, \
    .anim_8 = ANIM_ChuckQuizmo_Run, \
    .anim_9 = ANIM_ChuckQuizmo_Run, \
    .anim_A = ANIM_ChuckQuizmo_Run, \
    .anim_B = ANIM_ChuckQuizmo_Run, \
    .anim_C = ANIM_ChuckQuizmo_Run, \
    .anim_D = ANIM_ChuckQuizmo_Run, \
    .anim_E = ANIM_ChuckQuizmo_Run, \
    .anim_F = ANIM_ChuckQuizmo_Run, \
}
