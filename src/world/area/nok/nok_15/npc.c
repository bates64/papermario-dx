#include "nok_15.h"

#include "world/common/enemy/KoopaTroopa/wander.inc.c"
#include "world/common/enemy/Paratroopa/wander.inc.c"
#include "world/common/enemy/SpikedGoomba/wander.inc.c"

NpcData NpcData_KoopaTroopa = {
    .id = NPC_KoopaTroopa,
    .pos = $KoopaTroopa.pos,
    .yaw = $KoopaTroopa.yaw,
    .territory = $KoopaTroopa.territory,
    .settings = &NpcSettings_KoopaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = KOOPA_TROOPA_NOK_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_ParaTroopa = {
    .id = NPC_ParaTroopa,
    .pos = $ParaTroopa.pos,
    .yaw = $ParaTroopa.yaw,
    .territory = $ParaTroopa.territory,
    .settings = &NpcSettings_ParaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PARATROOPA_DROPS,
    .animations = PARATROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_KoopaTroopa, "nok:koopa_troopa_1_spiked_goomba_2", "nok_01"),
    NPC_GROUP(NpcData_ParaTroopa, "nok:paratroopa_1_koopa_troopa_1_spiked_goomba_2", "nok_01"),
    {}
};
