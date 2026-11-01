#include "isk_18.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BuzzyBeetle_01 = {
    .id = NPC_BuzzyBeetle_01,
    .pos = $BuzzyBeetle_01.pos,
    .yaw = $BuzzyBeetle_01.yaw,
    .territory = $BuzzyBeetle_01.territory,
    .initVarCount = 1,
    .initVar = { .value = Ref("isk_part_1:buzzy_beetle_1_buzzy_beetle_ceiling_1") },
    .settings = &NpcSettings_BuzzyBeetle_Ceiling,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcData NpcData_BuzzyBeetle_02 = {
    .id = NPC_BuzzyBeetle_02,
    .pos = $BuzzyBeetle_02.pos,
    .yaw = $BuzzyBeetle_02.yaw,
    .territory = $BuzzyBeetle_02.territory,
    .initVarCount = 1,
    .initVar = { .value = Ref("isk_part_1:buzzy_beetle_1_buzzy_beetle_ceiling_1_swooper_1") },
    .settings = &NpcSettings_BuzzyBeetle_Ceiling,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcData NpcData_BuzzyBeetle_03 = {
    .id = NPC_BuzzyBeetle_03,
    .pos = $BuzzyBeetle_03.pos,
    .yaw = $BuzzyBeetle_03.yaw,
    .territory = $BuzzyBeetle_03.territory,
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BuzzyBeetle_01, "isk_part_1:buzzy_beetle_ceiling_2", "isk_05"),
    NPC_GROUP(NpcData_BuzzyBeetle_02, "isk_part_1:buzzy_beetle_ceiling_2_swooper_1", "isk_05"),
    NPC_GROUP(NpcData_BuzzyBeetle_03, "isk_part_1:buzzy_beetle_1_swooper_1", "isk_05"),
    {}
};
