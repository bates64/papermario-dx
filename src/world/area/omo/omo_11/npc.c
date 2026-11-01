#include "omo_11.h"

#include "world/common/enemy/PyroGuy/wander.inc.c"

NpcData NpcData_PyroGuy_01 = {
    .id = NPC_PyroGuy_01,
    .pos = $PyroGuy_01.pos,
    .yaw = $PyroGuy_01.yaw,
    .territory = $PyroGuy_01.territory,
    .settings = &NpcSettings_PyroGuy_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PYRO_GUY_DROPS,
    .animations = PYRO_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_PyroGuy_02 = {
    .id = NPC_PyroGuy_02,
    .pos = $PyroGuy_02.pos,
    .yaw = $PyroGuy_02.yaw,
    .territory = $PyroGuy_02.territory,
    .settings = &NpcSettings_PyroGuy_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PYRO_GUY_DROPS,
    .animations = PYRO_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_PyroGuy_01, "omo:pyro_guy_1_spy_guy_1_groove_guy_1", "omo_06"),
    NPC_GROUP(NpcData_PyroGuy_02, "omo:pyro_guy_2_spy_guy_1", "omo_06"),
    {}
};
