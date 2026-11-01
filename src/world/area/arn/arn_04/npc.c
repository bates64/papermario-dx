#include "arn_04.h"

#include "world/common/enemy/HyperGoomba/patrol.inc.c"
#include "world/common/enemy/HyperParagoomba/wander.inc.c"
#include "world/common/enemy/HyperCleft/wander.inc.c"

NpcData NpcData_HyperParagoomba = {
    .id = NPC_HyperParagoomba,
    .pos = $HyperParagoomba.pos,
    .yaw = $HyperParagoomba.yaw,
    .territory = $HyperParagoomba.territory,
    .settings = &NpcSettings_HyperParagoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = HYPER_PARAGOOMBA_DROPS,
    .animations = HYPER_PARAGOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_HyperGoomba = {
    .id = NPC_HyperGoomba,
    .pos = $HyperGoomba.pos,
    .yaw = $HyperGoomba.yaw,
    .territory = $HyperGoomba.territory,
    .settings = &NpcSettings_HyperGoomba_Patrol,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = HYPER_GOOMBA_DROPS,
    .animations = HYPER_GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

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

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_HyperParagoomba, "arn:hyper_paragoomba_4", "arn_01"),
    NPC_GROUP(NpcData_HyperGoomba, "arn:hyper_goomba_2_hyper_paragoomba_1", "arn_01"),
    NPC_GROUP(NpcData_HyperCleft_01, "arn:hyper_cleft_3", "arn_01"),
    NPC_GROUP(NpcData_HyperCleft_02, "arn:hyper_cleft_2_hyper_goomba_2", "arn_01"),
    {}
};
