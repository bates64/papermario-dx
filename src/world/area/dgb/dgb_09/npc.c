#include "dgb_09.h"

#include "world/common/enemy/Clubba/wander.inc.c"
#include "world/common/enemy/Clubba/napping.inc.c"

#define AI_SENTINEL_FIRST_NPC NPC_Sentinel
#define AI_SENTINEL_LAST_NPC  NPC_Sentinel
#include "world/common/enemy/Sentinel/wander.inc.c"

NpcData NpcData_Clubba_Wander[] = {
    {
        .id = NPC_Clubba_Wander,
        .pos = $Clubba_Wander.pos,
        .yaw = $Clubba_Wander.yaw,
        .territory = $Clubba_Wander.territory,
        .settings = &NpcSettings_Clubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Wander_Hitbox),
};

EvtScript EVS_NpcInit_Clubba_Napping = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Dgb10.index)
        Call(SetNpcPos, NPC_SELF, 240, 0, 88)
        Call(InterpNpcYaw, NPC_SELF, 270, 0)
    EndIf
    Return
    End
};

NpcData NpcData_Clubba_Napping[] = {
    {
        .id = NPC_Clubba_Napping,
        .pos = $Clubba_Napping.pos,
        .yaw = $Clubba_Napping.yaw,
        .territory = $Clubba_Napping.territory,
        .init = &EVS_NpcInit_Clubba_Napping,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Napping_Hitbox),
};

NpcData NpcData_Sentinel = {
    .id = NPC_Sentinel,
    .pos = $Sentinel.pos,
    .yaw = $Sentinel.yaw,
    .territory = $Sentinel.territory,
    .settings = &NpcSettings_Sentinel_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = NO_DROPS,
    .animations = SENTINEL_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba_Wander, "dgb:clubba_4", "dgb_01"),
    NPC_GROUP(NpcData_Clubba_Napping, "dgb:clubba_2", "dgb_01"),
    NPC_GROUP(NpcData_Sentinel),
    {}
};
