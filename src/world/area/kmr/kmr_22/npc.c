#include "kmr_22.h"

#include "world/common/npc/Dummy/idle.inc.c"
#include "world/common/npc/StarSpirit/base.h"

#include "world/common/enemy/KoopaBros/base.h"
#include "world/common/enemy/TubbaBlubba/base.h"
#include "world/common/enemy/ShyGuy/base.h"
#include "world/common/enemy/HuffNPuff/base.h"
#include "world/common/enemy/RuffPuff/base.h"
#include "world/common/enemy/CrystalKing/base.h"
#include "world/common/npc/Bowser/base.h"

#include "npc/lava_piranha.inc.c"

#include "npc/chapter_1.inc.c"
#include "npc/chapter_2.inc.c"
#include "npc/chapter_3.inc.c"
#include "npc/chapter_4.inc.c"
#include "npc/chapter_5.inc.c"
#include "npc/chapter_6.inc.c"
#include "npc/chapter_7.inc.c"
#include "npc/chapter_8.inc.c"

NpcData N(NpcData_Chapter1)[] = {
    {
        .id = NPC_Eldstar,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Eldstar),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = ELDSTAR_ANIMS,
    },
    {
        .id = NPC_KoopaBros_01,
        .pos = { 10.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_KoopaBros),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_02,
        .pos = { 90.0f, 10.0f, 91.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_KoopaBros),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_03,
        .pos = { 86.0f, 0.0f, -7.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_KoopaBros),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_04,
        .pos = { 54.0f, -2.0f, -47.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_KoopaBros),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
};

NpcData N(NpcData_Chapter2)[] = {
    {
        .id = NPC_Mamar,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Mamar),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = MAMAR_ANIMS,
    },
    {
        .id = NPC_Tutankoopa,
        .pos = { 78.0f, 19.0f, 20.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Tutankoopa),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Tutankoopa_Idle,
            .walk   = ANIM_Tutankoopa_Idle,
            .run    = ANIM_Tutankoopa_Idle,
            .chase  = ANIM_Tutankoopa_Idle,
            .alert  = ANIM_Tutankoopa_Idle,
            .unused = ANIM_Tutankoopa_Idle,
            .death  = ANIM_Tutankoopa_Hurt,
            .hit    = ANIM_Tutankoopa_Hurt,
            .anim_8 = ANIM_Tutankoopa_Idle,
            .anim_9 = ANIM_Tutankoopa_Idle,
            .anim_A = ANIM_Tutankoopa_Idle,
            .anim_B = ANIM_Tutankoopa_Idle,
            .anim_C = ANIM_Tutankoopa_Idle,
            .anim_D = ANIM_Tutankoopa_Idle,
            .anim_E = ANIM_Tutankoopa_Idle,
            .anim_F = ANIM_Tutankoopa_Idle,
        },
    },
    {
        .id = NPC_ChainChomp_01,
        .pos = { 23.0f, -4.0f, -180.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ChainChomp),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_ChainChomp_Still,
            .walk   = ANIM_ChainChomp_Still,
            .run    = ANIM_ChainChomp_Still,
            .chase  = ANIM_ChainChomp_Still,
            .alert  = ANIM_ChainChomp_Still,
            .unused = ANIM_ChainChomp_Still,
            .death  = ANIM_ChainChomp_Still,
            .hit    = ANIM_ChainChomp_Still,
            .anim_8 = ANIM_ChainChomp_Still,
            .anim_9 = ANIM_ChainChomp_Still,
            .anim_A = ANIM_ChainChomp_Still,
            .anim_B = ANIM_ChainChomp_Still,
            .anim_C = ANIM_ChainChomp_Still,
            .anim_D = ANIM_ChainChomp_Still,
            .anim_E = ANIM_ChainChomp_Still,
            .anim_F = ANIM_ChainChomp_Still,
        },
    },
    {
        .id = NPC_ChainChomp_02,
        .pos = { 23.0f, -4.0f, -180.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_ChainChomp_Still,
            .walk   = ANIM_ChainChomp_Still,
            .run    = ANIM_ChainChomp_Still,
            .chase  = ANIM_ChainChomp_Still,
            .alert  = ANIM_ChainChomp_Still,
            .unused = ANIM_ChainChomp_Still,
            .death  = ANIM_ChainChomp_Still,
            .hit    = ANIM_ChainChomp_Still,
            .anim_8 = ANIM_ChainChomp_Still,
            .anim_9 = ANIM_ChainChomp_Still,
            .anim_A = ANIM_ChainChomp_Still,
            .anim_B = ANIM_ChainChomp_Still,
            .anim_C = ANIM_ChainChomp_Still,
            .anim_D = ANIM_ChainChomp_Still,
            .anim_E = ANIM_ChainChomp_Still,
            .anim_F = ANIM_ChainChomp_Still,
        },
    },
    {
        .id = NPC_ChainChomp_03,
        .pos = { 23.0f, -4.0f, -180.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_ChainChomp_Still,
            .walk   = ANIM_ChainChomp_Still,
            .run    = ANIM_ChainChomp_Still,
            .chase  = ANIM_ChainChomp_Still,
            .alert  = ANIM_ChainChomp_Still,
            .unused = ANIM_ChainChomp_Still,
            .death  = ANIM_ChainChomp_Still,
            .hit    = ANIM_ChainChomp_Still,
            .anim_8 = ANIM_ChainChomp_Still,
            .anim_9 = ANIM_ChainChomp_Still,
            .anim_A = ANIM_ChainChomp_Still,
            .anim_B = ANIM_ChainChomp_Still,
            .anim_C = ANIM_ChainChomp_Still,
            .anim_D = ANIM_ChainChomp_Still,
            .anim_E = ANIM_ChainChomp_Still,
            .anim_F = ANIM_ChainChomp_Still,
        },
    },
    {
        .id = NPC_ChainChomp_04,
        .pos = { 23.0f, -4.0f, -180.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_ChainChomp_Still,
            .walk   = ANIM_ChainChomp_Still,
            .run    = ANIM_ChainChomp_Still,
            .chase  = ANIM_ChainChomp_Still,
            .alert  = ANIM_ChainChomp_Still,
            .unused = ANIM_ChainChomp_Still,
            .death  = ANIM_ChainChomp_Still,
            .hit    = ANIM_ChainChomp_Still,
            .anim_8 = ANIM_ChainChomp_Still,
            .anim_9 = ANIM_ChainChomp_Still,
            .anim_A = ANIM_ChainChomp_Still,
            .anim_B = ANIM_ChainChomp_Still,
            .anim_C = ANIM_ChainChomp_Still,
            .anim_D = ANIM_ChainChomp_Still,
            .anim_E = ANIM_ChainChomp_Still,
            .anim_F = ANIM_ChainChomp_Still,
        },
    },
    {
        .id = NPC_ChainChomp_05,
        .pos = { 23.0f, -4.0f, -180.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_ChainChomp_Still,
            .walk   = ANIM_ChainChomp_Still,
            .run    = ANIM_ChainChomp_Still,
            .chase  = ANIM_ChainChomp_Still,
            .alert  = ANIM_ChainChomp_Still,
            .unused = ANIM_ChainChomp_Still,
            .death  = ANIM_ChainChomp_Still,
            .hit    = ANIM_ChainChomp_Still,
            .anim_8 = ANIM_ChainChomp_Still,
            .anim_9 = ANIM_ChainChomp_Still,
            .anim_A = ANIM_ChainChomp_Still,
            .anim_B = ANIM_ChainChomp_Still,
            .anim_C = ANIM_ChainChomp_Still,
            .anim_D = ANIM_ChainChomp_Still,
            .anim_E = ANIM_ChainChomp_Still,
            .anim_F = ANIM_ChainChomp_Still,
        },
    },
};

NpcData N(NpcData_Chapter3)[] = {
    {
        .id = NPC_Skolar,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Skolar),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = SKOLAR_ANIMS,
    },
    {
        .id = NPC_Tubba,
        .pos = { 54.0f, -1.0f, 1.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Tubba),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = TUBBA_ANIMS,
    },
};

NpcData N(NpcData_Chapter4)[] = {
    {
        .id = NPC_Muskular,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Muskular),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = MUSKULAR_ANIMS,
    },
    {
        .id = NPC_GeneralGuy,
        .pos = { 97.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_GeneralGuy),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_GeneralGuy_Idle,
            .walk   = ANIM_GeneralGuy_Idle,
            .run    = ANIM_GeneralGuy_Idle,
            .chase  = ANIM_GeneralGuy_Idle,
            .alert  = ANIM_GeneralGuy_Idle,
            .unused = ANIM_GeneralGuy_Idle,
            .death  = ANIM_GeneralGuy_Idle,
            .hit    = ANIM_GeneralGuy_Idle,
            .anim_8 = ANIM_GeneralGuy_Idle,
            .anim_9 = ANIM_GeneralGuy_Idle,
            .anim_A = ANIM_GeneralGuy_Idle,
            .anim_B = ANIM_GeneralGuy_Idle,
            .anim_C = ANIM_GeneralGuy_Idle,
            .anim_D = ANIM_GeneralGuy_Idle,
            .anim_E = ANIM_GeneralGuy_Idle,
            .anim_F = ANIM_GeneralGuy_Idle,
        },
    },
    {
        .id = NPC_ShyGuy_01,
        .pos = { 17.0f, 0.0f, -14.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ShyGuy),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_ShyGuy_02,
        .pos = { 47.0f, 0.0f, 25.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ShyGuy),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
};

NpcData N(NpcData_Chapter5)[] = {
    {
        .id = NPC_Misstar,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Misstar),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = MISSTAR_ANIMS,
    },
    {
        .id = NPC_LavaPiranhaHead,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_LavaPiranhaHead),
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_DO_NOT_KILL,
        .drops = NO_DROPS,
        .animations = LAVA_PIRANHA_HEAD_ANIMS,
        .limitAnimations = N(LimitAnims_LavaPiranha),
    },
    {
        .id = NPC_LavaBud_01,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_LavaBud),
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL,
        .drops = NO_DROPS,
        .animations = LAVA_PIRANHA_BUD_ANIMS,
        .limitAnimations = N(LimitAnims_LavaBud),
    },
    {
        .id = NPC_LavaBud_02,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_LavaBud),
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL,
        .drops = NO_DROPS,
        .animations = LAVA_PIRANHA_BUD_ANIMS,
        .limitAnimations = N(LimitAnims_LavaBud),
    },
};

NpcData N(NpcData_Chapter6)[] = {
    {
        .id = NPC_Klevar,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Klevar),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = KLEVAR_ANIMS,
    },
    {
        .id = NPC_HuffNPuff_Body,
        .pos = { 70.0f, 109.0f, 1.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_HuffNPuff_Body),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = HUFF_N_PUFF_ANIMS,
    },
    {
        .id = NPC_HuffNPuff_Face,
        .pos = { 70.0f, 109.0f, 1.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_HuffNPuff_Face),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = HUFF_N_PUFF_ANIMS,
    },
    {
        .id = NPC_HuffNPuff_Arms,
        .pos = { 70.0f, 109.0f, 1.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_HuffNPuff_Arms),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = HUFF_N_PUFF_ANIMS,
    },
    {
        .id = NPC_RuffPuff_01,
        .pos = { 60.0f, 40.0f, -50.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_RuffPuff_01),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RUFF_PUFF_ANIMS,
    },
    {
        .id = NPC_RuffPuff_02,
        .pos = { 14.0f, 61.0f, 1.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RUFF_PUFF_ANIMS,
    },
};

NpcData N(NpcData_Chapter7)[] = {
    {
        .id = NPC_Kalmar,
        .pos = { -62.0f, 96.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Kalmar),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = KALMAR_ANIMS,
    },
    {
        .id = NPC_CrystalKing,
        .pos = { 60.0f, -2.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_CrystalKing),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
    {
        .id = NPC_IceCube,
        .pos = { 10.0f, 31.0f, -12.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_IceCube),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
    {
        .id = NPC_IceSphere,
        .pos = { 40.0f, 68.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_IceSphere),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
    {
        .id = NPC_IceSpike,
        .pos = { 96.0f, 53.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_IceSpike),
        .settings = &N(NpcSettings_Dummy),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
};

NpcData N(NpcData_Chapter8) = {
    .id = NPC_Bowser,
    .pos = { 58.0f, 0.0f, 20.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Bowser),
    .settings = &N(NpcSettings_Dummy),
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
    .drops = NO_DROPS,
    .animations = BOWSER_ANIMS,
};

NpcGroupList N(NpcGroup_Chapter1) = {
    NPC_GROUP(N(NpcData_Chapter1)),
    {}
};

NpcGroupList N(NpcGroup_Chapter2) = {
    NPC_GROUP(N(NpcData_Chapter2)),
    {}
};

NpcGroupList N(NpcGroup_Chapter3) = {
    NPC_GROUP(N(NpcData_Chapter3)),
    {}
};

NpcGroupList N(NpcGroup_Chapter4) = {
    NPC_GROUP(N(NpcData_Chapter4)),
    {}
};

NpcGroupList N(NpcGroup_Chapter5) = {
    NPC_GROUP(N(NpcData_Chapter5)),
    {}
};

NpcGroupList N(NpcGroup_Chapter6) = {
    NPC_GROUP(N(NpcData_Chapter6)),
    {}
};

NpcGroupList N(NpcGroup_Chapter7) = {
    NPC_GROUP(N(NpcData_Chapter7)),
    {}
};

NpcGroupList N(NpcGroup_Chapter8) = {
    NPC_GROUP(N(NpcData_Chapter8)),
    {}
};
