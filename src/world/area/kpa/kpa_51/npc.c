
#include "kpa_51.h"

#include "world/common/enemy/Magikoopa/wander.inc.c"
#include "world/common/enemy/Koopatrol/wander.inc.c"

NpcData NpcData_Magikoopa_01[] = {
    {
        .id = NPC_Magikoopa_01,
        .pos = $Magikoopa_01.pos,
        .yaw = $Magikoopa_01.yaw,
        .territory = $Magikoopa_01.territory,
        .settings = &NpcSettings_Magikoopa_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = MAGIKOOPA_DROPS,
        .animations = MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_Magikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    MAGIKOOPA_SPELL_HITBOX(NPC_Magikoopa_01 + 1)
};

NpcData NpcData_Magikoopa_02[] = {
    {
        .id = NPC_Magikoopa_02,
        .pos = $Magikoopa_02.pos,
        .yaw = $Magikoopa_02.yaw,
        .territory = $Magikoopa_02.territory,
        .settings = &NpcSettings_Magikoopa_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = MAGIKOOPA_DROPS,
        .animations = MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_Magikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    MAGIKOOPA_SPELL_HITBOX(NPC_Magikoopa_02 + 1)
};

NpcData NpcData_Koopatrol = {
    .id = NPC_Koopatrol,
    .pos = $Koopatrol.pos,
    .yaw = $Koopatrol.yaw,
    .territory = $Koopatrol.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Magikoopa_01, "kpa:magikoopa_1_bony_beetle_1_magikoopa_1", "kpa_01"),
    NPC_GROUP(NpcData_Magikoopa_02, "kpa:magikoopa_2_flying_magikoopa_2", "kpa_01"),
    NPC_GROUP(NpcData_Koopatrol, "kpa:koopatrol_2_magikoopa_1_flying_magikoopa_1", "kpa_01"),
    {}
};
