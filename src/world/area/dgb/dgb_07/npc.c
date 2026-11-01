#include "dgb_07.h"

#include "world/common/enemy/Clubba/napping.inc.c"

NpcData NpcData_Clubba_01[] = {
    {
        .id = NPC_Clubba_01,
        .pos = $Clubba_01.pos,
        .yaw = $Clubba_01.yaw,
        .territory = $Clubba_01.territory,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_01_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba_01, "dgb:clubba_2", "dgb_03"),
    {}
};
