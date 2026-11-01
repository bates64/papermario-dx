#include "trd_02.h"

#include "world/common/enemy/Bobomb/wander.inc.c"
#include "world/common/enemy/KoopaTroopa/wander.inc.c"
#include "world/common/enemy/KoopaTroopa/patrol.inc.c"

NpcData NpcData_Bobomb_01 = {
    .id = NPC_Bobomb_01,
    .pos = $Bobomb_01.pos,
    .yaw = $Bobomb_01.yaw,
    .territory = $Bobomb_01.territory,
    .settings = &NpcSettings_Bobomb_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = BOBOMB_DROPS,
    .animations = BOBOMB_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bobomb_02 = {
    .id = NPC_Bobomb_02,
    .pos = $Bobomb_02.pos,
    .yaw = $Bobomb_02.yaw,
    .territory = $Bobomb_02.territory,
    .settings = &NpcSettings_Bobomb_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = BOBOMB_DROPS,
    .animations = BOBOMB_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_KoopaTroopa = {
    .id = NPC_KoopaTroopa,
    .pos = $KoopaTroopa.pos,
    .yaw = $KoopaTroopa.yaw,
    .territory = $KoopaTroopa.territory,
    .settings = &NpcSettings_KoopaTroopa_Patrol,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPA_TROOPA_TRD_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Bobomb_01, "trd_part_1:bob_omb_2", "trd_05:b"),
    NPC_GROUP(NpcData_Bobomb_02, "trd_part_1:bob_omb_2", "trd_05:b"),
    NPC_GROUP(NpcData_KoopaTroopa, "trd_part_1:koopa_troopa_2_bob_omb_2", "trd_05:e"),
    {}
};
