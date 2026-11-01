#include "iwa_03.h"

#include "world/common/enemy/MontyMole/ground_ambush.inc.c"
#include "world/common/enemy/Cleft/wander.inc.c"

NpcData NpcData_Cleft_01 = {
    .id = NPC_Cleft_01,
    .pos = $Cleft_01.pos,
    .yaw = $Cleft_01.yaw,
    .territory = $Cleft_01.territory,
    .settings = &NpcSettings_Cleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = CLEFT_DROPS,
    .animations = CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Cleft_02 = {
    .id = NPC_Cleft_02,
    .pos = $Cleft_02.pos,
    .yaw = $Cleft_02.yaw,
    .territory = $Cleft_02.territory,
    .settings = &NpcSettings_Cleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = CLEFT_DROPS,
    .animations = CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Cleft_03 = {
    .id = NPC_Cleft_03,
    .pos = $Cleft_03.pos,
    .yaw = $Cleft_03.yaw,
    .territory = $Cleft_03.territory,
    .settings = &NpcSettings_Cleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = CLEFT_DROPS,
    .animations = CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_MontyMole[] = {
    {
        .id = NPC_MontyMole,
        .pos = $MontyMole.pos,
        .yaw = $MontyMole.yaw,
        .territory = $MontyMole.territory,
        .settings = &NpcSettings_MontyMole_GroundAmbush,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = MONTY_MOLE_DROPS,
        .animations = MONTY_MOLE_AMBUSH_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    {
        .id = NPC_MontyMole_Hole,
        .pos = $MontyMole_Hole.pos,
        .yaw = $MontyMole_Hole.yaw,
        .territory = $MontyMole_Hole.territory,
        .settings = &NpcSettings_MontyMole_GroundAmbush_Hole,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DISABLE_AI | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = MONTY_MOLE_AMBUSH_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Cleft_01, "iwa:cleft_1_monty_mole_1", "iwa_01"),
    NPC_GROUP(NpcData_Cleft_02, "iwa:cleft_1", "iwa_01"),
    NPC_GROUP(NpcData_Cleft_03, "iwa:cleft_2", "iwa_01"),
    NPC_GROUP(NpcData_MontyMole, "iwa:monty_mole_1_cleft_1", "iwa_01"),
    {}
};
