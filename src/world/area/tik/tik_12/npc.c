#include "tik_12.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BuzzyBeetle = {
    .id = NPC_BuzzyBeetle,
    .pos = $BuzzyBeetle.pos,
    .yaw = $BuzzyBeetle.yaw,
    .territory = $BuzzyBeetle.territory,
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = TIK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BuzzyBeetle, "tik:buzzy_beetle_1_spiked_gloomba_1_buzzy_beetle_1", "tik_02"),
    {}
};
