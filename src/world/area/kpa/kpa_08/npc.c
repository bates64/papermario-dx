#include "kpa_08.h"

#include "world/common/enemy/Magikoopa/wander.inc.c"

NpcData NpcData_Magikoopa[] = {
    {
        .id = NPC_Magikoopa,
        .pos = $Magikoopa.pos,
        .yaw = $Magikoopa.yaw,
        .territory = $Magikoopa.territory,
        .settings = &NpcSettings_Magikoopa_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = MAGIKOOPA_DROPS,
        .animations = MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_Magikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    MAGIKOOPA_SPELL_HITBOX(NPC_Magikoopa_Spell)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Magikoopa, "kpa:magikoopa_2_dry_bones_1", "kpa_01:b"),
    {}
};
