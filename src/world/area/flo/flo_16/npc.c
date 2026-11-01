#include "flo_16.h"
#include "entity.h"

#include "world/common/enemy/RuffPuff/wander.inc.c"

NpcData NpcData_RuffPuff_01 = {
    .id = NPC_RuffPuff_01,
    .pos = $RuffPuff_01.pos,
    .yaw = $RuffPuff_01.yaw,
    .territory = $RuffPuff_01.territory,
    .settings = &NpcSettings_RuffPuff_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = RUFF_PUFF_DROPS,
    .animations = RUFF_PUFF_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_RuffPuff_02 = {
    .id = NPC_RuffPuff_02,
    .pos = $RuffPuff_02.pos,
    .yaw = $RuffPuff_02.yaw,
    .territory = $RuffPuff_02.territory,
    .settings = &NpcSettings_RuffPuff_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = RUFF_PUFF_DROPS,
    .animations = RUFF_PUFF_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_RuffPuff_01, "flo:ruff_puff_2_yellow_magikoopa_flying_1", "flo_02:c"),
    NPC_GROUP(NpcData_RuffPuff_02, "flo:ruff_puff_4", "flo_02:c"),
    {}
};
