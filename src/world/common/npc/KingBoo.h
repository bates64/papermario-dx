#include "common.h"
#include "sprite/npc/KingBoo.h"

#define KINGBOO_ANIMS \
{ \
    .idle   = ANIM_KingBoo_Idle, \
    .walk   = ANIM_KingBoo_Move, \
    .run    = ANIM_KingBoo_MoveFast, \
    .chase  = ANIM_KingBoo_MoveFast, \
    .anim_4 = ANIM_KingBoo_Idle, \
    .anim_5 = ANIM_KingBoo_Idle, \
    .death  = ANIM_KingBoo_Still, \
    .hit    = ANIM_KingBoo_Still, \
    .anim_8 = ANIM_KingBoo_MoveFast, \
    .anim_9 = ANIM_KingBoo_MoveFast, \
    .anim_A = ANIM_KingBoo_MoveFast, \
    .anim_B = ANIM_KingBoo_MoveFast, \
    .anim_C = ANIM_KingBoo_MoveFast, \
    .anim_D = ANIM_KingBoo_MoveFast, \
    .anim_E = ANIM_KingBoo_MoveFast, \
    .anim_F = ANIM_KingBoo_MoveFast, \
}
