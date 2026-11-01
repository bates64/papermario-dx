#include "mac_01.h"

NpcData NpcData_IntroNPCs[] = {
    {
        .id = NPC_Luigi,
        .pos = $Luigi.pos,
        .yaw = $Luigi.yaw,
        .settings = &NpcSettings_Luigi,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = LUIGI_ANIMS,
    },
    {
        .id = NPC_IntroToad1,
        .pos = $IntroToad1.pos,
        .yaw = $IntroToad1.yaw,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_RunsHisMouth,
    },
    {
        .id = NPC_IntroToad2,
        .pos = $IntroToad2.pos,
        .yaw = $IntroToad2.yaw,
        .territory = $IntroToad2.territory,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_MAC_PrincessFan,
    },
    {
        .id = NPC_IntroToad3,
        .pos = $IntroToad3.pos,
        .yaw = $IntroToad3.yaw,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_MAC_SeeksTheSouth,
    },
};

NpcGroupList IntroNPCs = {
    NPC_GROUP(NpcData_IntroNPCs),
    {}
};
