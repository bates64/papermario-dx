#pragma once
#include "npc.h"
#include "sprite/npc/GoombaBros.h"

#define GOOMBA_BROS_RED_ANIMS \
{ \
    .idle   = ANIM_GoombaBros_Red_Idle, \
    .walk   = ANIM_GoombaBros_Red_Walk, \
    .run    = ANIM_GoombaBros_Red_Run, \
    .chase  = ANIM_GoombaBros_Red_Run, \
    .alert  = ANIM_GoombaBros_Red_Idle, \
    .unused = ANIM_GoombaBros_Red_Idle, \
    .death  = ANIM_GoombaBros_Red_Hurt, \
    .hit    = ANIM_GoombaBros_Red_Hurt, \
    .anim_8 = ANIM_GoombaBros_Red_Run, \
    .anim_9 = ANIM_GoombaBros_Red_Run, \
    .anim_A = ANIM_GoombaBros_Red_Run, \
    .anim_B = ANIM_GoombaBros_Red_Run, \
    .anim_C = ANIM_GoombaBros_Red_Run, \
    .anim_D = ANIM_GoombaBros_Red_Run, \
    .anim_E = ANIM_GoombaBros_Red_Run, \
    .anim_F = ANIM_GoombaBros_Red_Run, \
}

#define GOOMBA_BROS_BLUE_ANIMS \
{ \
    .idle   = ANIM_GoombaBros_Blue_Idle, \
    .walk   = ANIM_GoombaBros_Blue_Walk, \
    .run    = ANIM_GoombaBros_Blue_Run, \
    .chase  = ANIM_GoombaBros_Blue_Run, \
    .alert  = ANIM_GoombaBros_Blue_Idle, \
    .unused = ANIM_GoombaBros_Blue_Idle, \
    .death  = ANIM_GoombaBros_Blue_Hurt, \
    .hit    = ANIM_GoombaBros_Blue_Hurt, \
    .anim_8 = ANIM_GoombaBros_Blue_Run, \
    .anim_9 = ANIM_GoombaBros_Blue_Run, \
    .anim_A = ANIM_GoombaBros_Blue_Run, \
    .anim_B = ANIM_GoombaBros_Blue_Run, \
    .anim_C = ANIM_GoombaBros_Blue_Run, \
    .anim_D = ANIM_GoombaBros_Blue_Run, \
    .anim_E = ANIM_GoombaBros_Blue_Run, \
    .anim_F = ANIM_GoombaBros_Blue_Run, \
}
