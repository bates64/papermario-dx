#include "hos_02.h"

#include "world/common/enemy/Ember/wander.inc.c"

NpcData NpcData_Ember = {
    .id = NPC_Ember_01,
    .pos = $Ember_01.pos,
    .yaw = $Ember_01.yaw,
    .territory = $Ember_01.territory,
    .settings = &NpcSettings_Ember_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = EMBER_DROPS,
    .animations = EMBER_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Ember_02 = {
    .id = NPC_Ember_02,
    .pos = $Ember_02.pos,
    .yaw = $Ember_02.yaw,
    .territory = $Ember_02.territory,
    .settings = &NpcSettings_Ember_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = EMBER_DROPS,
    .animations = EMBER_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Ember_03 = {
    .id = NPC_Ember_03,
    .pos = $Ember_03.pos,
    .yaw = $Ember_03.yaw,
    .territory = $Ember_03.territory,
    .settings = &NpcSettings_Ember_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = EMBER_DROPS,
    .animations = EMBER_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Ember, "hos:ember_2", "hos_01"),
    NPC_GROUP(NpcData_Ember_02, "hos:ember_2", "hos_01"),
    NPC_GROUP(NpcData_Ember_03, "hos:ember_2", "hos_01"),
    {}
};
