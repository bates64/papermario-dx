#include "dgb_02.h"

#include "world/common/enemy/Clubba/wander.inc.c"
#include "world/common/enemy/Clubba/napping.inc.c"

NpcData NpcData_Clubba_01[] = {
    {
        .id = NPC_Clubba_01,
        .pos = $Clubba_01.pos,
        .yaw = $Clubba_01.yaw,
        .territory = $Clubba_01.territory,
        .settings = &NpcSettings_Clubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_01_Hitbox),
};

NpcData NpcData_Clubba_02[] = {
    {
        .id = NPC_Clubba_02,
        .pos = $Clubba_02.pos,
        .yaw = $Clubba_02.yaw,
        .territory = $Clubba_02.territory,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_02_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba_01, "dgb:clubba_3", "dgb_01"),
    NPC_GROUP(NpcData_Clubba_02, "dgb:clubba_2", "dgb_01"),
    {}
};
