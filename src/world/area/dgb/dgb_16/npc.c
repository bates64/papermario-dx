#include "dgb_16.h"

#include "world/common/enemy/Clubba/napping.inc.c"

NpcData NpcData_Clubba_01[] = {
    {
        .id = NPC_Clubba_01,
        .pos = $Clubba_01.pos,
        .yaw = $Clubba_01.yaw,
        .territory = $Clubba_01.territory,
        .settings = &NpcSettings_Clubba_Napping,
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

NpcData NpcData_Clubba_03[] = {
    {
        .id = NPC_Clubba_03,
        .pos = $Clubba_03.pos,
        .yaw = $Clubba_03.yaw,
        .territory = $Clubba_03.territory,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_03_Hitbox),
};

NpcData NpcData_Clubba_04[] = {
    {
        .id = NPC_Clubba_04,
        .pos = $Clubba_04.pos,
        .yaw = $Clubba_04.yaw,
        .territory = $Clubba_04.territory,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_04_Hitbox),
};

NpcData NpcData_Clubba_05[] = {
    {
        .id = NPC_Clubba_05,
        .pos = $Clubba_05.pos,
        .yaw = $Clubba_05.yaw,
        .territory = $Clubba_05.territory,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_05_Hitbox),
};

NpcData NpcData_Clubba_06[] = {
    {
        .id = NPC_Clubba_06,
        .pos = $Clubba_06.pos,
        .yaw = $Clubba_06.yaw,
        .territory = $Clubba_06.territory,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_06_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba_01, "dgb:clubba_4", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_02, "dgb:clubba_1", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_03, "dgb:clubba_1", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_04, "dgb:clubba_1", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_05, "dgb:clubba_2", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_06, "dgb:clubba_2", "dgb_03"),
    {}
};
