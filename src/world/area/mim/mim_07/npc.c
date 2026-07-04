#include "mim_07.h"

#include "world/common/enemy/ForestFuzzy/wander.inc.c"

#include "world/common/npc/JrTroopa/idle.inc.c"

s32 N(JrTroopa_TriggerPos_South)[] = {
    0, -350,
};

s32 N(JrTroopa_TriggerPos_North)[] = {
    0, 350,
};

s32 N(JrTroopa_TriggerPos_East)[] = {
    350, 0,
};

s32 N(JrTroopaPath_SouthFromWest)[] = {
    -270, -245, -150, -310,
};

s32 N(JrTroopaPath_SouthFromEast)[] = {
    270, -245, 150, -310,
};

s32 N(JrTroopaPath_NorthFromWest)[] = {
    -270, 245, -150, 310,
};

s32 N(JrTroopaPath_NorthFromEast)[] = {
    270, 245, 150, 310,
};

s32 N(JrTroopaPath_EastFromSouth)[] = {
    245, -270, 310, -150,
};

s32 N(JrTroopaPath_EastFromNorth)[] = {
    245, 270, 310, 150,
};

EvtScript N(EVS_NpcIdle_JrTroopa) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(mim_07_ENTRY_0)
            UseBuf(Ref(N(JrTroopa_TriggerPos_South)))
        CaseEq(mim_07_ENTRY_1)
            UseBuf(Ref(N(JrTroopa_TriggerPos_South)))
        CaseEq(mim_07_ENTRY_2)
            UseBuf(Ref(N(JrTroopa_TriggerPos_North)))
        CaseEq(mim_07_ENTRY_3)
            UseBuf(Ref(N(JrTroopa_TriggerPos_East)))
    EndSwitch
    BufRead2(LVar1, LVar2)
    Call(AwaitPlayerApproach, LVar1, LVar2, 80)
    Label(10)
    Wait(1)
    Call(AwaitPlayerLeave, LVar1, LVar2, 100)
    Call(IsPlayerWithin, 0, 0, 410, LVar0)
    IfEq(LVar0, 0)
        Goto(10)
    EndIf
    Call(DisablePlayerInput, true)
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, PARTNER_NONE)
        Call(InterruptUsePartner)
        Wait(20)
    EndIf
    ExecWait(N(EVS_JrTroopaMusic))
    Call(GetPlayerPos, LVar1, LVar2, LVar3)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(mim_07_ENTRY_0)
            IfLt(LVar1, 0)
                UseBuf(Ref(N(JrTroopaPath_SouthFromWest)))
            Else
                UseBuf(Ref(N(JrTroopaPath_SouthFromEast)))
            EndIf
        CaseEq(mim_07_ENTRY_2)
            IfLt(LVar1, 0)
                UseBuf(Ref(N(JrTroopaPath_NorthFromWest)))
            Else
                UseBuf(Ref(N(JrTroopaPath_NorthFromEast)))
            EndIf
        CaseEq(mim_07_ENTRY_3)
            IfLt(LVar3, 0)
                UseBuf(Ref(N(JrTroopaPath_EastFromSouth)))
            Else
                UseBuf(Ref(N(JrTroopaPath_EastFromNorth)))
            EndIf
    EndSwitch
    BufRead4(LVar2, LVar3, LVar4, LVar5)
    Call(SetSelfVar, 0, LVar2)
    Call(SetSelfVar, 1, LVar3)
    Call(SetNpcPos, NPC_SELF, LVar2, 0, LVar3)
    Call(SpeakToPlayer, NPC_SELF, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Idle, 0, MSG_CH3_0018)
    Thread
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Add(LVar0, LVar4)
        Add(LVar2, LVar5)
        Div(LVar0, 2)
        Div(LVar2, 2)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Call(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Call(SetCamSpeed, CAM_DEFAULT, Float(4.0 / DT))
        Call(SetCamDistance, CAM_DEFAULT, Float(300.0))
        Call(SetCamPitch, CAM_DEFAULT, Float(20.0), Float(-6.0))
        Call(PanToTarget, CAM_DEFAULT, 0, true)
    EndThread
    Call(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_Run)
    Call(NpcMoveTo, NPC_SELF, LVar4, LVar5, 30)
    Call(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_Idle)
    Call(SpeakToPlayer, NPC_SELF, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Idle, 0, MSG_CH3_0019)
    Call(DisablePartnerAI, false)
    Call(GetCurrentPartnerID, LVar0)
    Switch(LVar0)
        CaseEq(PARTNER_GOOMBARIO)
            Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldGoombario_Talk, ANIM_WorldGoombario_Idle, 5, MSG_CH3_001A)
        CaseEq(PARTNER_KOOPER)
            Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldKooper_Talk, ANIM_WorldKooper_Idle, 5, MSG_CH3_001B)
        CaseEq(PARTNER_BOMBETTE)
            Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldBombette_Talk, ANIM_WorldBombette_Idle, 5, MSG_CH3_001C)
        CaseEq(PARTNER_PARAKARRY)
            Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldParakarry_Talk, ANIM_WorldParakarry_Idle, 5, MSG_CH3_001D)
        CaseEq(PARTNER_BOW)
            Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldBow_Talk, ANIM_WorldBow_Idle, 5, MSG_CH3_001E)
    EndSwitch
    Call(EnablePartnerAI)
    Call(SpeakToPlayer, NPC_SELF, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Idle, 0, MSG_CH3_001F)
    Call(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_ChargeArmsUp)
    Call(DisablePlayerInput, false)
    Call(StartBossBattle, SONG_JR_TROOPA_BATTLE)
    Return
    End
};

EvtScript N(EVS_NpcDefeat_JrTroopa) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Idle, 0, MSG_CH3_0022)
    Call(GetSelfVar, 0, LVar0)
    Call(GetSelfVar, 1, LVar1)
    IfGe(LVar1, 0)
        Call(InterpNpcYaw, NPC_SELF, 200, 0)
    Else
        Call(InterpNpcYaw, NPC_SELF, 330, 0)
    EndIf
    Call(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_ChargeArmsUp)
    Wait(10 * DT)
    Call(NpcMoveTo, NPC_SELF, LVar0, LVar1, 15)
    Set(GF_MIM10_Defeated_JrTroopa, true)
    ExecWait(N(EVS_PlayForestMusic))
    Call(ResetCam, CAM_DEFAULT, Float(4.0 / DT))
    Call(RemoveNpc, NPC_SELF)
    Return
    End
};

EvtScript N(EVS_NpcInit_JrTroopa) = {
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        IfEq(GF_MIM10_Defeated_JrTroopa, false)
            Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_JrTroopa)))
            Call(BindNpcDefeat, NPC_SELF, Ref(N(EVS_NpcDefeat_JrTroopa)))
            Return
        EndIf
    EndIf
    Call(RemoveNpc, NPC_SELF)
    Return
    End
};

EvtScript N(EVS_NpcInit_Fuzzy) = {
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        IfEq(GF_MIM10_Defeated_JrTroopa, false)
            Call(RemoveNpc, NPC_SELF)
        EndIf
    EndIf
    Return
    End
};

NpcData N(NpcData_Fuzzy_01) = {
    .id = NPC_Fuzzy_01,
    .pos = { -240.0f, 0.0f, -240.0f },
    .yaw = 0,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 0, 0, 0 },
            .wanderSize = { 400 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 400 },
        }
    },
    .init = &N(EVS_NpcInit_Fuzzy),
    .settings = &N(NpcSettings_ForestFuzzy_Wander),
    .flags = 0,
    .drops = FOREST_FUZZY_DROPS,
    .animations = FOREST_FUZZY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData N(NpcData_Fuzzy_02) = {
    .id = NPC_Fuzzy_02,
    .pos = { 270.0f, 0.0f, 200.0f },
    .yaw = 0,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 0, 0, 0 },
            .wanderSize = { 400 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 400 },
        }
    },
    .init = &N(EVS_NpcInit_Fuzzy),
    .settings = &N(NpcSettings_ForestFuzzy_Wander),
    .flags = 0,
    .drops = FOREST_FUZZY_DROPS,
    .animations = FOREST_FUZZY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData N(NpcData_JrTroopa) = {
    .id = NPC_JrTroopa,
    .pos = { -338.0f, 0.0f, 0.0f },
    .yaw = 0,
    .init = &N(EVS_NpcInit_JrTroopa),
    .settings = &N(NpcSettings_JrTroopa),
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = JR_TROOPA_ANIMS,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Fuzzy_01), BTL_MIM_FORMATION_02, BTL_MIM_STAGE_00),
    NPC_GROUP(N(NpcData_Fuzzy_02), BTL_MIM_FORMATION_06, BTL_MIM_STAGE_00),
    NPC_GROUP(N(NpcData_JrTroopa), BTL_KMR_3_FORMATION_04),
    {}
};
