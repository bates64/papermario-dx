#include "flo_09.h"

#include "world/common/enemy/CrazyDayzee/wander.inc.c"

#include "world/common/enemy/Bzzap/wander.inc.c"

#include "world/common/npc/Dummy/idle.inc.c"

EvtScript EVS_NpcAI_Bzzap_02 = {
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
                IfGt(LVar1, 0)
                    Call(GetPlayerPos, LVar0, LVar1, LVar2)
                    Call(SetNpcJumpscale, NPC_SELF, 0)
                    Call(NpcJump0, NPC_SELF, LVar0, 50, LVar2, 15)
                    Call(SetSelfVar, 0, 1)
                    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_Bzzap_Wander)
                EndIf
            CaseEq(2)
                Call(DisablePlayerInput, true)
                Wait(25)
                Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
                Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE, false)
                Call(SetSelfVar, 0, 0)
                Call(DisablePlayerInput, false)
        EndSwitch
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_NpcDefeat_Bzzap_02 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetSelfVar, 0, 2)
            Call(BindNpcAI, NPC_SELF, EVS_NpcAI_Bzzap_02)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Bzzap_02 = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcAI_Bzzap_02)
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_Bzzap_02)
    Return
    End
};

NpcData NpcData_Dayzee_01 = {
    .id = NPC_Dayzee_01,
    .pos = $Dayzee_01.pos,
    .yaw = $Dayzee_01.yaw,
    .territory = $Dayzee_01.territory,
    .settings = &NpcSettings_CrazyDayzee_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = CRAZY_DAYZEE_DROPS,
    .animations = CRAZY_DAYZEE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Dayzee_02 = {
    .id = NPC_Dayzee_02,
    .pos = $Dayzee_02.pos,
    .yaw = $Dayzee_02.yaw,
    .territory = $Dayzee_02.territory,
    .settings = &NpcSettings_CrazyDayzee_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = CRAZY_DAYZEE_DROPS,
    .animations = CRAZY_DAYZEE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Bzzap_01 = {
    .id = NPC_Bzzap_01,
    .pos = $Bzzap_01.pos,
    .yaw = $Bzzap_01.yaw,
    .territory = $Bzzap_01.territory,
    .settings = &NpcSettings_Bzzap_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BZZAP_DROPS,
    .animations = BZZAP_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Bzzap_02 = {
    .id = NPC_Bzzap_02,
    .pos = $Bzzap_02.pos,
    .yaw = $Bzzap_02.yaw,
    .territory = $Bzzap_02.territory,
    .init = &EVS_NpcInit_Bzzap_02,
    .settings = &NpcSettings_Dummy,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BZZAP_DROPS,
    .animations = BZZAP_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Dayzee_01, "flo:crazee_dayzee_2", "flo_02:b"),
    NPC_GROUP(NpcData_Dayzee_02, "flo:crazee_dayzee_2_bzzap_1", "flo_02:b"),
    NPC_GROUP(NpcData_Bzzap_01, "flo:bzzap_2", "flo_01:b"),
    NPC_GROUP(NpcData_Bzzap_02, "flo:bzzap_2", "flo_01:b"),
    {}
};
