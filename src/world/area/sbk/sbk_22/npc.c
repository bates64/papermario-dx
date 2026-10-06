#include "sbk_22.h"

#include "world/common/enemy/Bandit/wander.inc.c"
#include "world/common/enemy/Pokey/wander.inc.c"

NpcData NpcData_Pokey = {
    .id = NPC_Pokey,
    .pos = { -140.0f, 0.0f, -230.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -140, 0, -230 },
            .wanderSize = { 100 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit = {
    .id = NPC_Bandit,
    .pos = { 40.0f, 0.0f, 90.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 40, 0, 90 },
            .wanderSize = { 100 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Pokey, "sbk:pokey_2_bandit_1_pokey_1", "sbk_02"),
    NPC_GROUP(NpcData_Bandit, "sbk:bandit_2_pokey_1", "sbk_02"),
    {}
};
