#include "kpa_130.h"

#include "world/common/enemy/BombshellBill/base.h"

#include "world/common/ai/BulletBillAI.inc.c"

GuardAISettings AISettings_BillBlaster = {
    .playerSearchInterval = 30,
};

EvtScript EVS_NpcAI_BillBlaster = {
    Call(BillBlasterAI_Main, Ref(AISettings_BillBlaster))
    Return
    End
};

MobileAISettings AISettings_BulletBill = {
    .chaseSpeed = 3.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_BulletBill = {
    Call(EnemyEnableFirstStrike, true)
    Call(SetSelfVar, AI_VAR_BULLET_STATUS, BULLET_STATUS_IDLE)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Call(BulletBillAI_Main, Ref(AISettings_BulletBill))
    Return
    End
};

GuardAISettings AISettings_BombshellBlaster = {
    .playerSearchInterval = 10,
};

EvtScript EVS_NpcAI_BombshellBlaster = {
    Call(BillBlasterAI_Main, Ref(AISettings_BombshellBlaster))
    Return
    End
};

MobileAISettings AISettings_BombshellBill = {
    .chaseSpeed = 7.3f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_BombshellBill = {
    Call(EnemyEnableFirstStrike, true)
    Call(SetSelfVar, AI_VAR_BULLET_STATUS, BULLET_STATUS_IDLE)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Call(BulletBillAI_Main, Ref(AISettings_BombshellBill))
    Return
    End
};

EvtScript EVS_NpcDefeat_BombshellBlaster = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
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

EvtScript EVS_NpcDefeat_BulletBill = {
    Call(SetNpcRotation, NPC_SELF, 0, 0, 0)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(DoNpcDefeat)
            Call(SetSelfVar, AI_VAR_BULLET_STATUS, BULLET_STATUS_IDLE)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_BulletBill))
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(OnPlayerFled, false)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcDefeat_BombshellBill = {
    Call(SetNpcRotation, NPC_SELF, 0, 0, 0)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetSelfVar, AI_VAR_BULLET_STATUS, BULLET_STATUS_DONE)
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

NpcSettings NpcSettings_BillBlaster = {
    .height = 26,
    .radius = 32,
    .level = ACTOR_LEVEL_BILL_BLASTER,
    .doAI = &EVS_NpcAI_BillBlaster,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EVS_NpcDefeat_BombshellBlaster,
};

NpcSettings NpcSettings_BulletBill = {
    .height = 14,
    .radius = 31,
    .level = ACTOR_LEVEL_BULLET_BILL,
    .doAI = &EVS_NpcAI_BulletBill,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EVS_NpcDefeat_BulletBill,
};

NpcSettings NpcSettings_BombshellBlaster = {
    .height = 26,
    .radius = 32,
    .level = ACTOR_LEVEL_BOMBSHELL_BLASTER,
    .doAI = &EVS_NpcAI_BombshellBlaster,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EVS_NpcDefeat_BombshellBlaster,
};

NpcSettings NpcSettings_BombshellBill = {
    .height = 14,
    .radius = 31,
    .level = ACTOR_LEVEL_BOMBSHELL_BILL,
    .doAI = &EVS_NpcAI_BombshellBill,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EVS_NpcDefeat_BombshellBill,
};

EvtScript EVS_NpcInit_BombshellBlaster = {
    Call(SetSelfVar, AI_VAR_BLASTER_RANGE, -995)
    Return
    End
};

EvtScript EVS_NpcInit_BombshellBlaster_03 = {
    Call(SetSelfVar, AI_VAR_BLASTER_RANGE, 30)
    Return
    End
};

NpcData NpcData_BombshellBlaster_01[] = {
    {
        .id = NPC_BombshellBlaster_01,
        .pos = { -288.0f, 120.0f, 120.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
    {
        .id = NPC_BombshellBlaster_02,
        .pos = { -288.0f, 120.0f, 78.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
};

NpcData NpcData_BombshellBlaster_03[] = {
    {
        .id = NPC_BombshellBlaster_03,
        .pos = { -748.0f, 300.0f, -22.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster_03,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = BOMBSHELL_BLASTER_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
    {
        .id = NPC_BombshellBlaster_04,
        .pos = { -748.0f, 300.0f, 22.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster_03,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
};

NpcData NpcData_BombshellBlaster_05[] = {
    {
        .id = NPC_BombshellBlaster_05,
        .pos = { 30.0f, 480.0f, -122.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = BOMBSHELL_BLASTER_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
    {
        .id = NPC_BombshellBlaster_06,
        .pos = { 30.0f, 480.0f, -78.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
};

NpcData NpcData_BombshellBlaster_07[] = {
    {
        .id = NPC_BombshellBlaster_07,
        .pos = { 820.0f, 600.0f, -122.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = BOMBSHELL_BLASTER_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
    {
        .id = NPC_BombshellBlaster_08,
        .pos = { 820.0f, 600.0f, -78.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 0 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &EVS_NpcInit_BombshellBlaster,
        .settings = &NpcSettings_BombshellBlaster,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BOMBSHELL_BLASTER_ANIMS,
    },
};

NpcData NpcData_BombshellBill_01 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_01);
NpcData NpcData_BombshellBill_02 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_02);
NpcData NpcData_BombshellBill_03 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_03);
NpcData NpcData_BombshellBill_04 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_04);
NpcData NpcData_BombshellBill_05 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_05);
NpcData NpcData_BombshellBill_06 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_06);
NpcData NpcData_BombshellBill_07 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_07);
NpcData NpcData_BombshellBill_08 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_08);
NpcData NpcData_BombshellBill_09 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_09);
NpcData NpcData_BombshellBill_10 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_10);

// the following NPCs are unused
NpcData NpcData_BombshellBill_11 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_11);
NpcData NpcData_BombshellBill_12 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_12);
NpcData NpcData_BombshellBill_13 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_13);
NpcData NpcData_BombshellBill_14 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_14);
NpcData NpcData_BombshellBill_15 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_15);
NpcData NpcData_BombshellBill_16 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_16);
NpcData NpcData_BombshellBill_17 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_17);
NpcData NpcData_BombshellBill_18 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_18);
NpcData NpcData_BombshellBill_19 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_19);
NpcData NpcData_BombshellBill_20 = BOMBSHELL_BILL_NPC(NPC_BombshellBill_20);

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BombshellBlaster_01, BTL_KPA4_FORMATION_02, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBlaster_03, BTL_KPA4_FORMATION_02, BTL_KPA4_STAGE_05),
    NPC_GROUP(NpcData_BombshellBlaster_05, BTL_KPA4_FORMATION_03, BTL_KPA4_STAGE_05),
    NPC_GROUP(NpcData_BombshellBlaster_07, BTL_KPA4_FORMATION_04, BTL_KPA4_STAGE_05),
    NPC_GROUP(NpcData_BombshellBill_01, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_02, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_03, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_04, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_05, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_06, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_07, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_08, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_09, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    NPC_GROUP(NpcData_BombshellBill_10, BTL_KPA4_FORMATION_01, BTL_KPA4_STAGE_04),
    {}
};
