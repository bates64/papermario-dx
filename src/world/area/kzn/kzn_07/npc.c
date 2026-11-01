#include "kzn_07.h"
#include "effects.h"

#include "world/common/enemy/LavaBubble/wander.inc.c"

NpcData NpcData_LavaBubble_01 = {
    .id = NPC_Bubble_01,
    .pos = $Bubble_01.pos,
    .yaw = $Bubble_01.yaw,
    .territory = $Bubble_01.territory,
    .settings = &NpcSettings_LavaBubble_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = LAVA_BUBBLE_DROPS,
    .animations = LAVA_BUBBLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_LavaBubble_02 = {
    .id = NPC_Bubble_02,
    .pos = $Bubble_02.pos,
    .yaw = $Bubble_02.yaw,
    .territory = $Bubble_02.territory,
    .settings = &NpcSettings_LavaBubble_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = LAVA_BUBBLE_DROPS,
    .animations = LAVA_BUBBLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_LavaBubble_01, "kzn:lava_bubble_2_red_magikoopa_1", "kzn_01:b"),
    NPC_GROUP(NpcData_LavaBubble_02, "kzn:lava_bubble_2_white_magikoopa_1", "kzn_01:b"),
    {}
};
