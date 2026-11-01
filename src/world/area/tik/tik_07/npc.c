#include "tik_07.h"

#include "world/common/enemy/Paragloomba/wander.inc.c"

NpcData NpcData_Paragloomba_01 = {
    .id = NPC_Paragoomba_01,
    .pos = $Paragoomba_01.pos,
    .yaw = $Paragoomba_01.yaw,
    .territory = $Paragoomba_01.territory,
    .settings = &NpcSettings_Paragloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PARAGLOOMBA_DROPS,
    .animations = PARAGLOOMBA_ANIMS,
};

NpcData NpcData_Paragloomba_02 = {
    .id = NPC_Paragoomba_02,
    .pos = $Paragoomba_02.pos,
    .yaw = $Paragoomba_02.yaw,
    .territory = $Paragoomba_02.territory,
    .settings = &NpcSettings_Paragloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PARAGLOOMBA_DROPS,
    .animations = PARAGLOOMBA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Paragloomba_01, "tik:paragloomba_3", "tik_02"),
    NPC_GROUP(NpcData_Paragloomba_02, "tik:paragloomba_1_spiked_gloomba_1", "tik_02"),
    {}
};
