#include "kpa_61.h"

#include "world/common/enemy/Koopatrol/wander.inc.c"
#include "world/common/enemy/FlyingMagikoopa/wander.inc.c"

NpcData NpcData_Koopatrol_01 = {
    .id = NPC_Koopatrol_01,
    .pos = $Koopatrol_01.pos,
    .yaw = $Koopatrol_01.yaw,
    .territory = $Koopatrol_01.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_Koopatrol_02 = {
    .id = NPC_Koopatrol_02,
    .pos = $Koopatrol_02.pos,
    .yaw = $Koopatrol_02.yaw,
    .territory = $Koopatrol_02.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_FlyingMagikoopa_01[] = {
    {
        .id = NPC_FlyingMagikoopa_01,
        .pos = $FlyingMagikoopa_01.pos,
        .yaw = $FlyingMagikoopa_01.yaw,
        .territory = $FlyingMagikoopa_01.territory,
        .settings = &NpcSettings_FlyingMagikoopa_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = FLYING_MAGIKOOPA_DROPS,
        .animations = FLYING_MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_FlyingMagikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FLYING_MAGIKOOPA_SPELL_HITBOX(NPC_FlyingMagikoopa_01_Spell),
};

NpcData NpcData_FlyingMagikoopa_02[] = {
    {
        .id = NPC_FlyingMagikoopa_02,
        .pos = $FlyingMagikoopa_02.pos,
        .yaw = $FlyingMagikoopa_02.yaw,
        .territory = $FlyingMagikoopa_02.territory,
        .settings = &NpcSettings_FlyingMagikoopa_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = FLYING_MAGIKOOPA_DROPS,
        .animations = FLYING_MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_FlyingMagikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FLYING_MAGIKOOPA_SPELL_HITBOX(NPC_FlyingMagikoopa_02_Spell),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Koopatrol_01, "kpa:koopatrol_1_dry_bones_2", "kpa_07"),
    NPC_GROUP(NpcData_Koopatrol_02, "kpa:koopatrol_1_bony_beetle_2", "kpa_07"),
    NPC_GROUP(NpcData_FlyingMagikoopa_01, "kpa:flying_magikoopa_1_dry_bones_2", "kpa_07"),
    NPC_GROUP(NpcData_FlyingMagikoopa_02, "kpa:flying_magikoopa_1_koopatrol_2", "kpa_07"),
    {}
};
