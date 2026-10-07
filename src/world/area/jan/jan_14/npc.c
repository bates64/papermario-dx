#include "jan_14.h"

#include "world/common/enemy/JungleFuzzy/base.h"

// uses base fuzzy includes instead of JungleFuzzy!
#include "world/common/enemy/Fuzzy/wander.inc.c"
#include "world/common/enemy/Fuzzy/idle.inc.c"

EvtScript EVS_NpcIdle_JungleFuzzy = {
    Label(0)
    Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    IfGt(LVar1, 40)
        Wait(1)
        Goto(0)
    EndIf
    Wait(45)
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_Fuzzy_Wander))
    Return
    End
};

EvtScript EVS_NpcDefeat_Unused = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(RemoveNpc, NPC_SELF)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_JungleFuzzy = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_JungleFuzzy))
    Return
    End
};

NpcData NpcData_JungleFuzzy_01 = {
    .id = NPC_JungleFuzzy_01,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &EVS_NpcInit_JungleFuzzy,
    .settings = &NpcSettings_Fuzzy,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = JUNGLE_FUZZY_DROPS,
    .animations = JUNGLE_FUZZY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_JungleFuzzy_02 = {
    .id = NPC_JungleFuzzy_02,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &EVS_NpcInit_JungleFuzzy,
    .settings = &NpcSettings_Fuzzy,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = JUNGLE_FUZZY_DROPS,
    .animations = JUNGLE_FUZZY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_JungleFuzzy_01, "jan:jungle_fuzzy_2", "jan_03"),
    NPC_GROUP(NpcData_JungleFuzzy_02, "jan:jungle_fuzzy_3", "jan_03"),
    {}
};
