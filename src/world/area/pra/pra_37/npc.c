#include "pra_37.h"

#include "world/common/enemy/FrostClubba/wander.inc.c"

EvtScript EVS_NpcInit_FrostClubba = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_REFLECT_FLOOR, true)
    Return
    End
};

NpcData NpcData_FrostClubba[] = {
    {
        .id = NPC_FrostClubba,
        .pos = $FrostClubba.pos,
        .yaw = $FrostClubba.yaw,
        .territory = $FrostClubba.territory,
        .init = &EVS_NpcInit_FrostClubba,
        .settings = &NpcSettings_FrostClubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = FROST_CLUBBA_DROPS,
        .animations = FROST_CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    FROST_CLUBBA_MACE_HITBOX(NPC_FrostClubba_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_FrostClubba, "pra:white_clubba_2_mixed_0d", "pra_01"),
    {}
};
