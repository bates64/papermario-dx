#include "mim_08.h"

#include "world/common/enemy/Bzzap/wander.inc.c"

#include "world/common/enemy/PiranhaPlant/idle.inc.c"

EvtScript EVS_NpcIdle_Bzzap = {
    Label(100)
        Wait(1)
        IfEq(MV_HitHiveTree, false)
            Goto(100)
        EndIf
    Call(SetNpcPos, NPC_SELF, -280, 108, 0)
    Call(SetNpcJumpscale, NPC_SELF, 0.0)
    Call(NpcJump1, NPC_SELF, -280, 50, 10, 5)
    Wait(50)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_Bzzap_Wander)
    Return
    End
};

EvtScript EVS_NpcInit_Bzzap = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Bzzap)
    Return
    End
};

NpcData NpcData_Bzzap = {
    .id = NPC_Bzzap,
    .pos = $Bzzap.pos,
    .yaw = $Bzzap.yaw,
    .territory = $Bzzap.territory,
    .init = &EVS_NpcInit_Bzzap,
    .settings = &NpcSettings_Bzzap_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = NO_DROPS,
    .animations = BZZAP_ANIMS,
};

NpcData NpcData_PiranhaPlant_01[] = {
    {
        .id = NPC_PiranhaPlant_01,
        .pos = $PiranhaPlant_01.pos,
        .yaw = $PiranhaPlant_01.yaw,
        .territory = $PiranhaPlant_01.territory,
        .settings = &NpcSettings_PiranhaPlant,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_01_Hitbox)
};

NpcData NpcData_PiranhaPlant_02[] = {
    {
        .id = NPC_PiranhaPlant_02,
        .pos = $PiranhaPlant_02.pos,
        .yaw = $PiranhaPlant_02.yaw,
        .territory = $PiranhaPlant_02.territory,
        .settings = &NpcSettings_PiranhaPlant,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_02_Hitbox)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Bzzap, "mim:bzzap_2", "mim_01"),
    NPC_GROUP(NpcData_PiranhaPlant_01, "mim:piranha_plant_1_forest_fuzzy_1_piranha_plant_1", "mim_01"),
    NPC_GROUP(NpcData_PiranhaPlant_02, "mim:piranha_plant_2", "mim_01"),
    {}
};
