#include "tik_05.h"

#include "world/common/enemy/SpikedGloomba/wander.inc.c"

NpcData NpcData_SpikedGloomba_01 = {
    .id = NPC_SpikedGoomba_01,
    .pos = $SpikedGoomba_01.pos,
    .yaw = $SpikedGoomba_01.yaw,
    .territory = $SpikedGoomba_01.territory,
    .settings = &NpcSettings_SpikedGloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = SPIKED_GLOOMBA_DROPS,
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcData NpcData_SpikedGloomba_02 = {
    .id = NPC_SpikedGoomba_02,
    .pos = $SpikedGoomba_02.pos,
    .yaw = $SpikedGoomba_02.yaw,
    .territory = $SpikedGoomba_02.territory,
    .settings = &NpcSettings_SpikedGloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = SPIKED_GLOOMBA_DROPS,
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpikedGloomba_01, "tik:spiked_gloomba_1_buzzy_beetle_2", "tik_01"),
    NPC_GROUP(NpcData_SpikedGloomba_02, "tik:spiked_gloomba_1_mixed_12", "tik_01"),
    {}
};
