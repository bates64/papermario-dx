#include "kkj_03.h"
#include "sprite/player.h"

#include "world/common/npc/Peach/idle.inc.c"

NpcData NpcData_Peach = {
    .id = NPC_Peach,
    .pos = { 670.0f, 0.0f, -12.0f },
    .yaw = 270,
    .settings = &NpcSettings_Peach,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE,
    .drops = NO_DROPS,
    .animations = PEACH_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Peach),
    {}
};
