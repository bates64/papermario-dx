#include "pra_35.h"

#include "world/common/enemy/FrostClubba/patrol.inc.c"
#include "world/common/enemy/Duplighost/patrol.inc.c"

EvtScript EVS_NpcInit_EnableReflection = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_REFLECT_FLOOR, true)
    Return
    End
};

NpcData NpcData_Clubba[] = {
    {
        .id = NPC_Clubba,
        .pos = $Clubba.pos,
        .yaw = $Clubba.yaw,
        .territory = $Clubba.territory,
        .init = &EVS_NpcInit_EnableReflection,
        .settings = &NpcSettings_FrostClubba_Patrol,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = FROST_CLUBBA_DROPS,
        .animations = FROST_CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FROST_CLUBBA_MACE_HITBOX(NPC_Clubba_Hitbox),
};

NpcData NpcData_Duplighost = {
    .id = NPC_Duplighost,
    .pos = $Duplighost.pos,
    .yaw = $Duplighost.yaw,
    .territory = $Duplighost.territory,
    .init = &EVS_NpcInit_EnableReflection,
    .settings = &NpcSettings_Duplighost_Patrol,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = DUPLIGHOST_DROPS,
    .animations = DUPLIGHOST_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba, "pra:white_clubba_2_yellow_magikoopa_1", "pra_02"),
    NPC_GROUP(NpcData_Duplighost, "pra3:duplighost_4", "pra_01"),
    {}
};
