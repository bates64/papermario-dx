#include "kpa_115.h"

#include "world/common/enemy/HammerBros/wander.inc.c"

NpcData NpcData_HammerBros[] = {
    {
        .id = NPC_HammerBros,
        .pos = $HammerBros.pos,
        .yaw = $HammerBros.yaw,
        .territory = $HammerBros.territory,
        .settings = &NpcSettings_HammerBros_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = HAMMER_BROS_DROPS,
        .animations = HAMMER_BROS_ANIMS,
    },
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 1),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 2),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 3),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 4),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 5),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 6),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_HammerBros, "kpa:hammer_bro_1_dry_bones_1_hammer_bro_1_magikoopa_1", "kpa_13"),
    {}
};
