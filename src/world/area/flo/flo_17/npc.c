#include "flo_17.h"

#include "world/common/npc/Dummy/idle.inc.c"

#define AI_LAKITU_FIRST_SPINY_ID    NPC_Spiny_01
#define AI_LAKITU_LAST_SPINY_ID     NPC_Spiny_04
#include "world/common/enemy/Lakitu/spiny_spawner.inc.c"

NpcData NpcData_Lakitu_01 = {
    .id = NPC_Lakitu_01,
    .pos = $Lakitu_01.pos,
    .yaw = $Lakitu_01.yaw,
    .territory = $Lakitu_01.territory,
    .settings = &NpcSettings_Lakitu_SpinySpawner,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = LAKITU_DROPS,
    .animations = LAKITU_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Lakitu_02 = {
    .id = NPC_Lakitu_02,
    .pos = $Lakitu_02.pos,
    .yaw = $Lakitu_02.yaw,
    .territory = $Lakitu_02.territory,
    .settings = &NpcSettings_Lakitu_SpinySpawner,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = LAKITU_DROPS,
    .animations = LAKITU_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Spiny_01 = {
    .id = NPC_Spiny_01,
    .pos = $Spiny_01.pos,
    .yaw = $Spiny_01.yaw,
    .territory = $Spiny_01.territory,
    .settings = &NpcSettings_SpawnedSpiny,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Spiny_02 = {
    .id = NPC_Spiny_02,
    .pos = $Spiny_02.pos,
    .yaw = $Spiny_02.yaw,
    .territory = $Spiny_02.territory,
    .settings = &NpcSettings_SpawnedSpiny,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Spiny_03 = {
    .id = NPC_Spiny_03,
    .pos = $Spiny_03.pos,
    .yaw = $Spiny_03.yaw,
    .territory = $Spiny_03.territory,
    .settings = &NpcSettings_SpawnedSpiny,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Spiny_04 = {
    .id = NPC_Spiny_04,
    .pos = $Spiny_04.pos,
    .yaw = $Spiny_04.yaw,
    .territory = $Spiny_04.territory,
    .settings = &NpcSettings_SpawnedSpiny,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPINY_DROPS,
    .animations = SPINY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Lakitu_01, "flo:lakitu_2_white_magikoopa_1", "flo_01:c"),
    NPC_GROUP(NpcData_Lakitu_02, "flo:lakitu_2_red_magikoopa_1", "flo_01:c"),
    NPC_GROUP(NpcData_Spiny_01, "flo:spiny_2", "flo_01:c"),
    NPC_GROUP(NpcData_Spiny_02, "flo:spiny_2", "flo_01:c"),
    NPC_GROUP(NpcData_Spiny_03, "flo:spiny_2", "flo_01:c"),
    NPC_GROUP(NpcData_Spiny_04, "flo:spiny_2", "flo_01:c"),
    {}
};
