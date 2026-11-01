#include "tik_23.h"

#include "world/common/enemy/Spiny/wander.inc.c"

NpcData NpcData_Spiny_01 = {
    .id = NPC_Spiny_01,
    .pos = $Spiny_01.pos,
    .yaw = $Spiny_01.yaw,
    .territory = $Spiny_01.territory,
    .settings = &NpcSettings_Spiny_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Spiny_02 = {
    .id = NPC_Spiny_02,
    .pos = $Spiny_02.pos,
    .yaw = $Spiny_02.yaw,
    .territory = $Spiny_02.territory,
    .settings = &NpcSettings_Spiny_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Spiny_03 = {
    .id = NPC_Spiny_03,
    .pos = $Spiny_03.pos,
    .yaw = $Spiny_03.yaw,
    .territory = $Spiny_03.territory,
    .settings = &NpcSettings_Spiny_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Spiny_01, "tik:spiny_2", "tik_04"),
    NPC_GROUP(NpcData_Spiny_02, "tik:spiny_3", "tik_04"),
    NPC_GROUP(NpcData_Spiny_03, "tik:spiny_2", "tik_04"),
    {}
};
