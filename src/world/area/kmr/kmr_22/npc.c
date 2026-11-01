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

NpcData NpcData_Chapter1[] = {
    {
        .id = NPC_Eldstar,
        .pos = $Eldstar.pos,
        .yaw = $Eldstar.yaw,
        .init = &EVS_NpcInit_Eldstar,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = ELDSTAR_ANIMS,
    },
    {
        .id = NPC_KoopaBros_01,
        .pos = $KoopaBros_01.pos,
        .yaw = $KoopaBros_01.yaw,
        .init = &EVS_NpcInit_KoopaBros,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_02,
        .pos = $KoopaBros_02.pos,
        .yaw = $KoopaBros_02.yaw,
        .init = &EVS_NpcInit_KoopaBros,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_03,
        .pos = $KoopaBros_03.pos,
        .yaw = $KoopaBros_03.yaw,
        .init = &EVS_NpcInit_KoopaBros,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_04,
        .pos = $KoopaBros_04.pos,
        .yaw = $KoopaBros_04.yaw,
        .init = &EVS_NpcInit_KoopaBros,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
};

NpcData NpcData_Chapter2[] = {
    {
        .id = NPC_Mamar,
        .pos = $Mamar.pos,
        .yaw = $Mamar.yaw,
        .init = &EVS_NpcInit_Mamar,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = MAMAR_ANIMS,
    },
    {
        .id = NPC_Tutankoopa,
        .pos = $Tutankoopa.pos,
        .yaw = $Tutankoopa.yaw,
        .init = &EVS_NpcInit_Tutankoopa,
        .settings = &NpcSettings_Dummy,
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
        .pos = $ChainChomp_01.pos,
        .yaw = $ChainChomp_01.yaw,
        .init = &EVS_NpcInit_ChainChomp,
        .settings = &NpcSettings_Dummy,
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
        .pos = $ChainChomp_02.pos,
        .yaw = $ChainChomp_02.yaw,
        .settings = &NpcSettings_Dummy,
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
        .pos = $ChainChomp_03.pos,
        .yaw = $ChainChomp_03.yaw,
        .settings = &NpcSettings_Dummy,
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
        .pos = $ChainChomp_04.pos,
        .yaw = $ChainChomp_04.yaw,
        .settings = &NpcSettings_Dummy,
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
        .pos = $ChainChomp_05.pos,
        .yaw = $ChainChomp_05.yaw,
        .settings = &NpcSettings_Dummy,
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

NpcData NpcData_Chapter3[] = {
    {
        .id = NPC_Skolar,
        .pos = $Skolar.pos,
        .yaw = $Skolar.yaw,
        .init = &EVS_NpcInit_Skolar,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = SKOLAR_ANIMS,
    },
    {
        .id = NPC_Tubba,
        .pos = $Tubba.pos,
        .yaw = $Tubba.yaw,
        .init = &EVS_NpcInit_Tubba,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = TUBBA_ANIMS,
    },
};

NpcData NpcData_Chapter4[] = {
    {
        .id = NPC_Muskular,
        .pos = $Muskular.pos,
        .yaw = $Muskular.yaw,
        .init = &EVS_NpcInit_Muskular,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = MUSKULAR_ANIMS,
    },
    {
        .id = NPC_GeneralGuy,
        .pos = $GeneralGuy.pos,
        .yaw = $GeneralGuy.yaw,
        .init = &EVS_NpcInit_GeneralGuy,
        .settings = &NpcSettings_Dummy,
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
        .pos = $ShyGuy_01.pos,
        .yaw = $ShyGuy_01.yaw,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_ShyGuy_02,
        .pos = $ShyGuy_02.pos,
        .yaw = $ShyGuy_02.yaw,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
};

NpcData NpcData_Chapter5[] = {
    {
        .id = NPC_Misstar,
        .pos = $Misstar.pos,
        .yaw = $Misstar.yaw,
        .init = &EVS_NpcInit_Misstar,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = MISSTAR_ANIMS,
    },
    {
        .id = NPC_LavaPiranhaHead,
        .pos = $LavaPiranhaHead.pos,
        .yaw = $LavaPiranhaHead.yaw,
        .init = &EVS_NpcInit_LavaPiranhaHead,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_DO_NOT_KILL,
        .drops = NO_DROPS,
        .animations = LAVA_PIRANHA_HEAD_ANIMS,
        .limitAnimations = LimitAnims_LavaPiranha,
    },
    {
        .id = NPC_LavaBud_01,
        .pos = $LavaBud_01.pos,
        .yaw = $LavaBud_01.yaw,
        .init = &EVS_NpcInit_LavaBud,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL,
        .drops = NO_DROPS,
        .animations = LAVA_PIRANHA_BUD_ANIMS,
        .limitAnimations = LimitAnims_LavaBud,
    },
    {
        .id = NPC_LavaBud_02,
        .pos = $LavaBud_02.pos,
        .yaw = $LavaBud_02.yaw,
        .init = &EVS_NpcInit_LavaBud,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL,
        .drops = NO_DROPS,
        .animations = LAVA_PIRANHA_BUD_ANIMS,
        .limitAnimations = LimitAnims_LavaBud,
    },
};

NpcData NpcData_Chapter6[] = {
    {
        .id = NPC_Klevar,
        .pos = $Klevar.pos,
        .yaw = $Klevar.yaw,
        .init = &EVS_NpcInit_Klevar,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = KLEVAR_ANIMS,
    },
    {
        .id = NPC_HuffNPuff_Body,
        .pos = $HuffNPuff_Body.pos,
        .yaw = $HuffNPuff_Body.yaw,
        .init = &EVS_NpcInit_HuffNPuff_Body,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = HUFF_N_PUFF_ANIMS,
    },
    {
        .id = NPC_HuffNPuff_Face,
        .pos = $HuffNPuff_Face.pos,
        .yaw = $HuffNPuff_Face.yaw,
        .init = &EVS_NpcInit_HuffNPuff_Face,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = HUFF_N_PUFF_ANIMS,
    },
    {
        .id = NPC_HuffNPuff_Arms,
        .pos = $HuffNPuff_Arms.pos,
        .yaw = $HuffNPuff_Arms.yaw,
        .init = &EVS_NpcInit_HuffNPuff_Arms,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = HUFF_N_PUFF_ANIMS,
    },
    {
        .id = NPC_RuffPuff_01,
        .pos = $RuffPuff_01.pos,
        .yaw = $RuffPuff_01.yaw,
        .init = &EVS_NpcInit_RuffPuff_01,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RUFF_PUFF_ANIMS,
    },
    {
        .id = NPC_RuffPuff_02,
        .pos = $RuffPuff_02.pos,
        .yaw = $RuffPuff_02.yaw,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = RUFF_PUFF_ANIMS,
    },
};

NpcData NpcData_Chapter7[] = {
    {
        .id = NPC_Kalmar,
        .pos = $Kalmar.pos,
        .yaw = $Kalmar.yaw,
        .init = &EVS_NpcInit_Kalmar,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = KALMAR_ANIMS,
    },
    {
        .id = NPC_CrystalKing,
        .pos = $CrystalKing.pos,
        .yaw = $CrystalKing.yaw,
        .init = &EVS_NpcInit_CrystalKing,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
    {
        .id = NPC_IceCube,
        .pos = $IceCube.pos,
        .yaw = $IceCube.yaw,
        .init = &EVS_NpcInit_IceCube,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
    {
        .id = NPC_IceSphere,
        .pos = $IceSphere.pos,
        .yaw = $IceSphere.yaw,
        .init = &EVS_NpcInit_IceSphere,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
    {
        .id = NPC_IceSpike,
        .pos = $IceSpike.pos,
        .yaw = $IceSpike.yaw,
        .init = &EVS_NpcInit_IceSpike,
        .settings = &NpcSettings_Dummy,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = CRYSTAL_KING_ANIMS,
    },
};

NpcData NpcData_Chapter8 = {
    .id = NPC_Bowser,
    .pos = $Bowser.pos,
    .yaw = $Bowser.yaw,
    .init = &EVS_NpcInit_Bowser,
    .settings = &NpcSettings_Dummy,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
    .drops = NO_DROPS,
    .animations = BOWSER_ANIMS,
};

NpcGroupList NpcGroup_Chapter1 = {
    NPC_GROUP(NpcData_Chapter1),
    {}
};

NpcGroupList NpcGroup_Chapter2 = {
    NPC_GROUP(NpcData_Chapter2),
    {}
};

NpcGroupList NpcGroup_Chapter3 = {
    NPC_GROUP(NpcData_Chapter3),
    {}
};

NpcGroupList NpcGroup_Chapter4 = {
    NPC_GROUP(NpcData_Chapter4),
    {}
};

NpcGroupList NpcGroup_Chapter5 = {
    NPC_GROUP(NpcData_Chapter5),
    {}
};

NpcGroupList NpcGroup_Chapter6 = {
    NPC_GROUP(NpcData_Chapter6),
    {}
};

NpcGroupList NpcGroup_Chapter7 = {
    NPC_GROUP(NpcData_Chapter7),
    {}
};

NpcGroupList NpcGroup_Chapter8 = {
    NPC_GROUP(NpcData_Chapter8),
    {}
};
