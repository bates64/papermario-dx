#pragma once
#include "npc.h"
#include "sprite/npc/KoopaWithoutShell.h"

#define KOOPA_WITHOUT_SHELL_ANIMS \
{ \
    .idle   = ANIM_KoopaWithoutShell_CryIdle, \
    .walk   = ANIM_KoopaWithoutShell_CryRun, \
    .run    = ANIM_KoopaWithoutShell_Walk, \
    .chase  = ANIM_KoopaWithoutShell_CryRun, \
    .alert  = ANIM_KoopaWithoutShell_Walk, \
    .unused = ANIM_KoopaWithoutShell_Walk, \
    .death  = ANIM_KoopaWithoutShell_Still, \
    .hit    = ANIM_KoopaWithoutShell_Still, \
    .anim_8 = ANIM_KoopaWithoutShell_Still, \
    .anim_9 = ANIM_KoopaWithoutShell_Still, \
    .anim_A = ANIM_KoopaWithoutShell_Still, \
    .anim_B = ANIM_KoopaWithoutShell_Still, \
    .anim_C = ANIM_KoopaWithoutShell_Still, \
    .anim_D = ANIM_KoopaWithoutShell_Still, \
    .anim_E = ANIM_KoopaWithoutShell_Still, \
    .anim_F = ANIM_KoopaWithoutShell_Still, \
}
