#include "nok_13.h"

#include "world/common/enemy/Fuzzy/wander.inc.c"

NpcData NpcData_Fuzzy = {
    .id = NPC_UnusedFuzzy,
    .pos = $UnusedFuzzy.pos,
    .yaw = $UnusedFuzzy.yaw,
    .territory = $UnusedFuzzy.territory,
    .settings = &NpcSettings_Fuzzy_Wander,
    .drops = FUZZY_DROPS,
    .animations = FUZZY_ANIMS,
};

NpcGroupList DefaultNPCs = {
    {}
};
