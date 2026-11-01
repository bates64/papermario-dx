#include "arn_02.h"

#include "world/common/enemy/HyperGoomba/wander.inc.c"
#include "world/common/enemy/HyperCleft/wander.inc.c"

NpcData NpcData_HyperCleft_01 = {
    .id = NPC_HyperCleft_01,
    .pos = $HyperCleft_01.pos,
    .yaw = $HyperCleft_01.yaw,
    .territory = $HyperCleft_01.territory,
    .settings = &NpcSettings_HyperCleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = HYPER_CLEFT_DROPS,
    .animations = HYPER_CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_HyperCleft_02 = {
    .id = NPC_HyperCleft_02,
    .pos = $HyperCleft_02.pos,
    .yaw = $HyperCleft_02.yaw,
    .territory = $HyperCleft_02.territory,
    .settings = &NpcSettings_HyperCleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = HYPER_CLEFT_DROPS,
    .animations = HYPER_CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_HyperGoomba = {
    .id = NPC_HyperGoomba,
    .pos = $HyperGoomba.pos,
    .yaw = $HyperGoomba.yaw,
    .territory = $HyperGoomba.territory,
    .settings = &NpcSettings_HyperGoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = HYPER_GOOMBA_DROPS,
    .animations = HYPER_GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_HyperCleft_01, "arn:hyper_cleft_1", "arn_01"),
    NPC_GROUP(NpcData_HyperCleft_02, "arn:hyper_cleft_1_hyper_goomba_2", "arn_01"),
    NPC_GROUP(NpcData_HyperGoomba, "arn:hyper_goomba_2_hyper_paragoomba_1", "arn_01"),
    {}
};
