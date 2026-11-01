#include "dgb_03.h"

#include "world/common/enemy/Clubba/wander.inc.c"
#include "world/common/enemy/Clubba/patrol.inc.c"
#include "world/common/enemy/Clubba/napping.inc.c"

EvtScript EVS_NpcInit_Clubba_Napping = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Dgb14.index)
        Call(SetNpcPos, NPC_SELF, -330, 210, -20)
    EndIf
    Return
    End
};

NpcData NpcData_Clubba_Wander[] = {
    {
        .id = NPC_Clubba_Wander,
        .pos = $Clubba_Wander.pos,
        .yaw = $Clubba_Wander.yaw,
        .territory = $Clubba_Wander.territory,
        .settings = &NpcSettings_Clubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Wander_Hitbox),
};

NpcData NpcData_Clubba_Patrol[] = {
    {
        .id = NPC_Clubba_Patrol,
        .pos = $Clubba_Patrol.pos,
        .yaw = $Clubba_Patrol.yaw,
        .territory = $Clubba_Patrol.territory,
        .settings = &NpcSettings_Clubba_Patrol,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Patrol_Hitbox),
};

NpcData NpcData_Clubba_Napping[] = {
    {
        .id = NPC_Clubba_Napping,
        .pos = $Clubba_Napping.pos,
        .yaw = $Clubba_Napping.yaw,
        .territory = $Clubba_Napping.territory,
        .init = &EVS_NpcInit_Clubba_Napping,
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Napping_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba_Wander, "dgb:clubba_2", "dgb_02"),
    NPC_GROUP(NpcData_Clubba_Patrol, "dgb:clubba_2", "dgb_02"),
    NPC_GROUP(NpcData_Clubba_Napping, "dgb:clubba_4", "dgb_01"),
    {}
};
