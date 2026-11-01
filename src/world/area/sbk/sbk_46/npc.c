#include "sbk_46.h"

#include "world/common/enemy/Bandit/wander.inc.c"
#include "world/common/enemy/Pokey/wander.inc.c"

NpcData NpcData_Pokey = {
    .id = NPC_Pokey,
    .pos = $Pokey.pos,
    .yaw = $Pokey.yaw,
    .territory = $Pokey.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_FLYING,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit_01 = {
    .id = NPC_Bandit_01,
    .pos = $Bandit_01.pos,
    .yaw = $Bandit_01.yaw,
    .territory = $Bandit_01.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_FLYING,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit_02 = {
    .id = NPC_Bandit_02,
    .pos = $Bandit_02.pos,
    .yaw = $Bandit_02.yaw,
    .territory = $Bandit_02.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_FLYING,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Pokey, "sbk:pokey_2_bandit_2", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_01, "sbk:bandit_1_pokey_1", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_02, "sbk:bandit_4", "sbk_02"),
    {}
};
