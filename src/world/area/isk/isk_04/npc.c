#include "isk_04.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BuzzyBeetle_01 = {
    .id = NPC_BuzzyBeetle_01,
    .pos = $BuzzyBeetle_01.pos,
    .yaw = $BuzzyBeetle_01.yaw,
    .territory = $BuzzyBeetle_01.territory,
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcData NpcData_BuzzyBeetle_02 = {
    .id = NPC_BuzzyBeetle_02,
    .pos = $BuzzyBeetle_02.pos,
    .yaw = $BuzzyBeetle_02.yaw,
    .territory = $BuzzyBeetle_02.territory,
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BuzzyBeetle_01, "isk_part_1:buzzy_beetle_2", "isk_02:b"),
    NPC_GROUP(NpcData_BuzzyBeetle_02, "isk_part_1:buzzy_beetle_2", "isk_02:b"),
    {}
};
