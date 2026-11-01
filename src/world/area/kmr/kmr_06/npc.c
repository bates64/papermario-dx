#include "kmr_06.h"

#include "world/common/enemy/SpikedGoomba/wander.inc.c"
#include "world/common/enemy/Paragoomba/wander.inc.c"

NpcData NpcData_SpikedGoomba = {
    .id = NPC_SpikedGoomba,
    .pos = $SpikedGoomba.pos,
    .yaw = $SpikedGoomba.yaw,
    .territory = $SpikedGoomba.territory,
    .settings = &NpcSettings_SpikedGoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = SPIKED_GOOMBA_DROPS,
    .animations = SPIKED_GOOMBA_ANIMS,
};

NpcData NpcData_Paragoomba = {
    .id = NPC_Paragoomba,
    .pos = $Paragoomba.pos,
    .yaw = $Paragoomba.yaw,
    .territory = $Paragoomba.territory,
    .settings = &NpcSettings_Paragoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PARAGOOMBA_DROPS,
    .animations = PARAGOOMBA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpikedGoomba, "kmr_part_1:spiked_goomba_1_goomba_1", "kmr_04"),
    NPC_GROUP(NpcData_Paragoomba, "kmr_part_1:paragoomba_3", "kmr_04"),
    {}
};
