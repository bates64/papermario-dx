#include "sam_08.h"
#include "world/common/npc/Kooper/base.h"

NpcSettings N(NpcSettings_Kooper) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPA_TROOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

#include "world/common/enemy/Duplighost/disguised.inc.c"

#include "world/common/enemy/FrostClubba/wander.inc.c"

EvtScript N(EVS_NpcInteract_TrueKooperA) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKooper_Talk, ANIM_WorldKooper_Idle, 0, MSG_CH7_012B)
    Return
    End
};

EvtScript N(EVS_NpcHit_TrueKooperB) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            ExecWait(N(EVS_Scene_HitTrueKooper))
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInteract_FakeKooperA) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKooper_Talk, ANIM_WorldKooper_Idle, 0, MSG_CH7_012A)
    Return
    End
};

EvtScript N(EVS_NpcHit_FakeKooperB) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            ExecWait(N(EVS_Scene_HitFakeKooper))
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcIdle_Duplighost) = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, 0)
            Goto(0)
        EndIf
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript N(EVS_NpcDefeat_Duplighost) = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetNpcFlagBits, NPC_Duplighost, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
            Call(SetNpcSpeed, NPC_Duplighost, Float(3.0 / DT))
            Call(SetNpcJumpscale, NPC_Duplighost, Float(1.5))
            Call(SetNpcAnimation, NPC_Duplighost, ANIM_Duplighost_Run)
            Call(GetNpcPos, NPC_Duplighost, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Call(PlaySoundAtNpc, NPC_Duplighost, SOUND_DUPLIGHOST_STEP, SOUND_SPACE_DEFAULT)
            Call(NpcJump0, NPC_Duplighost, LVar0, LVar1, LVar2, 13 * DT)
            Call(InterpPlayerYaw, 90, 0)
            Call(InterpNpcYaw, NPC_PARTNER, 90, 0)
            Add(LVar0, 50)
            Call(PlaySoundAtNpc, NPC_Duplighost, SOUND_DUPLIGHOST_STEP, SOUND_SPACE_DEFAULT)
            Call(NpcJump0, NPC_Duplighost, LVar0, LVar1, LVar2, 13 * DT)
            Add(LVar0, 50)
            Call(PlaySoundAtNpc, NPC_Duplighost, SOUND_DUPLIGHOST_STEP, SOUND_SPACE_DEFAULT)
            Call(NpcJump0, NPC_Duplighost, LVar0, LVar1, LVar2, 13 * DT)
            Set(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
            Call(SetPlayerFlagBits, PS_FLAG_NO_CHANGE_PARTNER | PS_FLAG_NO_PARTNER_USAGE, false)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o47, COLLIDER_FLAGS_UPPER_MASK)
            Call(DisablePlayerInput, false)
            Add(LVar0, 50)
            Call(PlaySoundAtNpc, NPC_Duplighost, SOUND_DUPLIGHOST_STEP, SOUND_SPACE_DEFAULT)
            Call(NpcJump0, NPC_Duplighost, LVar0, LVar1, LVar2, 20 * DT)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_TrueKooperA) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_TrueKooperA)))
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_RealKooperA) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_FakeKooperA)))
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_Duplighost) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Duplighost)))
    Call(BindNpcDefeat, NPC_SELF, Ref(N(EVS_NpcDefeat_Duplighost)))
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

NpcData N(NpcData_Ambush)[] = {
    {
        .id = NPC_Kooper_01A,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_TrueKooperA),
        .settings = &N(NpcSettings_Kooper),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER | ENEMY_FLAG_NO_DROPS,
        .drops = NO_DROPS,
        .animations = KOOPER_ANIMS,
    },
    {
        .id = NPC_Kooper_02A,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_RealKooperA),
        .settings = &N(NpcSettings_Kooper),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER | ENEMY_FLAG_NO_DROPS,
        .drops = NO_DROPS,
        .animations = KOOPER_ANIMS,
    },
    {
        .id = NPC_Duplighost,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Duplighost),
        .settings = &N(NpcSettings_Duplighost),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER | ENEMY_FLAG_NO_DROPS,
        .drops = NO_DROPS,
        .animations = DUPLIGHOST_ANIMS,
    },
};

EvtScript N(EVS_NpcIdle_TrueKooperB) = {
    Loop(0)
        Call(GetNpcPos, NPC_Kooper_01A, LVar0, LVar1, LVar2)
        Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcInit_TrueKooperB) = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_PASSIVE, false)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_TrueKooperB)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_TrueKooperB)))
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcIdle_FakeKooperB) = {
    Loop(0)
        Call(GetNpcPos, NPC_Kooper_02A, LVar0, LVar1, LVar2)
        Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcInit_FakeKooperB) = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_PASSIVE, false)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_FakeKooperB)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_FakeKooperB)))
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

NpcData N(NpcData_Hittable)[] = {
    {
        .id = NPC_Kooper_01B,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_TrueKooperB),
        .settings = &N(NpcSettings_Kooper),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_HAS_NO_SPRITE | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER | ENEMY_FLAG_NO_DROPS | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP,
        .drops = NO_DROPS,
        .animations = KOOPER_ANIMS,
    },
    {
        .id = NPC_Kooper_02B,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_FakeKooperB),
        .settings = &N(NpcSettings_Kooper),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_HAS_NO_SPRITE | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER | ENEMY_FLAG_NO_DROPS | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP,
        .drops = NO_DROPS,
        .animations = KOOPER_ANIMS,
    },
};

NpcData N(NpcData_FrostClubba)[] = {
    {
        .id = NPC_Clubba_01,
        .pos = { -450.0f, 0.0f, -90.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -450, 0, -90 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { -450, 0, -90 },
                .detectSize = { 200 },
            }
        },
        .settings = &N(NpcSettings_FrostClubba_Wander),
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = FROST_CLUBBA_DROPS,
        .animations = FROST_CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FROST_CLUBBA_MACE_HITBOX(NPC_Clubba_02),
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Ambush), BTL_SAM_FORMATION_00, BTL_SAM_STAGE_04),
    NPC_GROUP(N(NpcData_Hittable), BTL_SAM_FORMATION_00, BTL_SAM_STAGE_04),
    NPC_GROUP(N(NpcData_FrostClubba), BTL_SAM_FORMATION_0B, BTL_SAM_STAGE_04),
    {}
};
