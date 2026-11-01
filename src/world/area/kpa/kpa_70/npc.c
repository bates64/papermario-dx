#include "kpa_70.h"

#include "world/common/enemy/Koopatrol/wander.inc.c"

NpcData NpcData_Koopatrol_01 = {
    .id = NPC_Koopatrol_01,
    .pos = $Koopatrol_01.pos,
    .yaw = $Koopatrol_01.yaw,
    .territory = $Koopatrol_01.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_Koopatrol_02 = {
    .id = NPC_Koopatrol_02,
    .pos = $Koopatrol_02.pos,
    .yaw = $Koopatrol_02.yaw,
    .territory = $Koopatrol_02.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Koopatrol_01, "kpa:koopatrol_2", "kpa_02"),
    NPC_GROUP(NpcData_Koopatrol_02, "kpa:koopatrol_3", "kpa_02"),
    {}
};
