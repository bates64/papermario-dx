#include "isk_08.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BuzzyBeetle = {
    .id = NPC_BuzzyBeetle,
    .pos = $BuzzyBeetle.pos,
    .yaw = $BuzzyBeetle.yaw,
    .territory = $BuzzyBeetle.territory,
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BuzzyBeetle, "isk_part_1:buzzy_beetle_4", "isk_02:b"),
    {}
};
