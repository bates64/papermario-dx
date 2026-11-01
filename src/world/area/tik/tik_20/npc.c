#include "tik_20.h"

#include "world/common/enemy/DarkTroopa/wander.inc.c"

NpcData NpcData_DarkTroopa_01 = {
    .id = NPC_DarkTroopa_01,
    .pos = $DarkTroopa_01.pos,
    .yaw = $DarkTroopa_01.yaw,
    .territory = $DarkTroopa_01.territory,
    .settings = &NpcSettings_DarkTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = DARK_TROOPA_DROPS,
    .animations = DARK_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_DarkTroopa_02 = {
    .id = NPC_DarkTroopa_02,
    .pos = $DarkTroopa_02.pos,
    .yaw = $DarkTroopa_02.yaw,
    .territory = $DarkTroopa_02.territory,
    .settings = &NpcSettings_DarkTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = DARK_TROOPA_DROPS,
    .animations = DARK_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_DarkTroopa_01, "tik:dark_koopa_1_spike_top_2", "tik_04"),
    NPC_GROUP(NpcData_DarkTroopa_02, "tik:dark_koopa_1_spike_top_1_dark_koopa_1", "tik_04"),
    {}
};
