#include "trd_04.h"

extern EvtScript EVS_DropSwitch;

#include "world/common/enemy/KoopaTroopa/wander.inc.c"
#include "world/common/enemy/KoopaTroopa/patrol.inc.c"
#include "world/common/enemy/Paratroopa/wander.inc.c"

EvtScript EVS_NpcDefeat_KoopaTroopa = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Set(GB_StoryProgress, STORY_CH1_DEFEATED_BASEMENT_GUARD)
            Thread
                Call(DoNpcDefeat)
            EndThread
            ExecWait(EVS_DropSwitch)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_KoopaTroopa = {
    IfGe(GB_StoryProgress, STORY_CH1_DEFEATED_BASEMENT_GUARD)
        Call(RemoveNpc, NPC_SELF)
        Return
    EndIf
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_KoopaTroopa))
    Return
    End
};

NpcData NpcData_KoopaTroopa_Wander = {
    .id = NPC_KoopaTroopa,
    .pos = { 0.0f, 0.0f, 125.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 0, 0, 125 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 125 },
            .detectSize = { 200 },
        }
    },
    .settings = &NpcSettings_KoopaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = KOOPA_TROOPA_TRD_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_KoopaTroopa_Patrol = {
    .id = NPC_KoopaTroopa,
    .pos = { 220.0f, 0.0f, 30.0f },
    .yaw = 90,
    .territory = {
        .patrol = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .numPoints  = 2,
            .points  = {
                { 220, 0, 30 },
                { 240, 0, 160 },
            },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 220, 0, 30 },
            .detectSize = { 200 },
        }
    },
    .init = &EVS_NpcInit_KoopaTroopa,
    .settings = &NpcSettings_KoopaTroopa_Patrol,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_ParaTroopa = {
    .id = NPC_ParaTroopa,
    .pos = { -5.0f, 237.0f, 157.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -5, 237, 157 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -5, 237, 157 },
            .detectSize = { 200 },
        }
    },
    .settings = &NpcSettings_ParaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PARATROOPA_DROPS,
    .animations = PARATROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList NpcGroupAfter = {
    NPC_GROUP(NpcData_KoopaTroopa_Wander, "trd_part_1:koopa_troopa_1_bob_omb_3", "trd_05e"),
    NPC_GROUP(NpcData_ParaTroopa, "trd_part_1:paratroopa_1_bob_omb_2", "trd_02d"),
    {}
};

NpcGroupList NpcGroupBefore = {
    NPC_GROUP(NpcData_KoopaTroopa_Patrol, "trd_part_1:koopa_troopa_1_bob_omb_3", "trd_05e"),
    NPC_GROUP(NpcData_ParaTroopa, "trd_part_1:paratroopa_1_bob_omb_2", "trd_02d"),
    {}
};
