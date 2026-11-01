#include "trd_07.h"

extern EvtScript EVS_RestoreMagicDoors;

#include "world/common/enemy/KoopaTroopa/wander.inc.c"
#include "world/common/enemy/Paratroopa/wander.inc.c"

EvtScript EVS_NpcDefeat_KoopaTroopa = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(GetRemainingEnemyCount, LVar0)
            IfEq(LVar0, 1)
                Set(GF_TRD07_Defeated_DungeonAmbush, true)
                Exec(EVS_RestoreMagicDoors)
            EndIf
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(OnPlayerFled, false)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_KoopaTroopa = {
    Call(SetSelfEnemyFlags, ENEMY_FLAG_NO_DROPS)
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_KoopaTroopa)
    IfEq(GF_TRD07_Defeated_DungeonAmbush, true)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

NpcData NpcData_KoopaTroopa = {
    .id = NPC_KoopaTroopa,
    .pos = $KoopaTroopa.pos,
    .yaw = $KoopaTroopa.yaw,
    .territory = $KoopaTroopa.territory,
    .init = &EVS_NpcInit_KoopaTroopa,
    .settings = &NpcSettings_KoopaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .drops = KOOPA_TROOPA_TRD_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
};

NpcData NpcData_ParaTroopa_01 = {
    .id = NPC_ParaTroopa_01,
    .pos = $ParaTroopa_01.pos,
    .yaw = $ParaTroopa_01.yaw,
    .territory = $ParaTroopa_01.territory,
    .init = &EVS_NpcInit_KoopaTroopa,
    .settings = &NpcSettings_ParaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .drops = PARATROOPA_DROPS,
    .animations = PARATROOPA_ANIMS,
};

NpcData NpcData_ParaTroopa_02 = {
    .id = NPC_ParaTroopa_02,
    .pos = $ParaTroopa_02.pos,
    .yaw = $ParaTroopa_02.yaw,
    .territory = $ParaTroopa_02.territory,
    .init = &EVS_NpcInit_KoopaTroopa,
    .settings = &NpcSettings_ParaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .drops = PARATROOPA_DROPS,
    .animations = PARATROOPA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_KoopaTroopa, "trd_part_1:koopa_troopa_2", "trd_02:b"),
    NPC_GROUP(NpcData_ParaTroopa_01, "trd_part_1:paratroopa_2", "trd_02:b"),
    NPC_GROUP(NpcData_ParaTroopa_02, "trd_part_1:paratroopa_1_koopa_troopa_1", "trd_02:b"),
    {}
};
