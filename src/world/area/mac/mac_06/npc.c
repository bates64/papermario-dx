#include "mac_06.h"
#include "model.h"
#include "effects.h"
#include "world/common/prefab/Whale.h"

#define CLONED_MODEL_GULL   CLONED_MODEL(1000)

#include "world/common/npc/Whale/idle.inc.c"
#include "world/common/npc/Kolorado/idle.inc.c"
#include "world/common/npc/JrTroopa/idle.inc.c"

enum WhaleRider {
    WHALE_RIDER_PLAYER      = 0,
    WHALE_RIDER_PARTNER     = 1,
    WHALE_RIDER_KOLORADO    = 2,
};

enum WhaleSpoutState {
    SPOUT_STATE_READY       = 0,
    SPOUT_STATE_BEGIN       = 10,
    SPOUT_STATE_RISING      = 11,
    SPOUT_STATE_FALLING     = 12,
};

s32 N(SpoutState) = SPOUT_STATE_READY;
f32 N(SpoutHeight) = 0.0f;
f32 N(SpoutVelocity) = 0.0f;
s32 N(SpoutInputWindow) = 0;

API_CALLABLE(N(UpdateWhaleRiderPosition)) {
    Bytecode* args = script->ptrReadPos;
    Npc* whale = get_npc_safe(NPC_Whale);
    Npc* kolorado;
    Npc* partner;
    f32 forward, radius;
    f32 x, y, z;

    if (isInitialCall) {
        script->functionTemp[0] = evt_get_variable(script, *args++);
        switch (script->functionTemp[0]) {
            case WHALE_RIDER_PLAYER:
                script->functionTemp[1] = 70;
                break;
            case WHALE_RIDER_PARTNER:
                script->functionTemp[1] = 100;
                break;
            case WHALE_RIDER_KOLORADO:
                script->functionTemp[1] = 40;
               break;
        }
    }

    radius = script->functionTemp[1];
    forward = -whale->yaw;
    x = whale->pos.x + 30.0f + sin_deg(forward) * radius;
    z = whale->pos.z + cos_deg(forward) * radius;
    y = whale->pos.y + 50.0f;

    switch (script->functionTemp[0]) {
        case WHALE_RIDER_PLAYER:
            gPlayerStatus.pos.x = x;
            gPlayerStatus.pos.y = y + N(SpoutHeight);
            gPlayerStatus.pos.z = z;
            whale->colliderPos.x = whale->pos.x;
            whale->colliderPos.y = whale->pos.y;
            whale->colliderPos.z = whale->pos.z;
            whale->flags |= NPC_FLAG_DIRTY_SHADOW;
            break;
        case WHALE_RIDER_PARTNER:
            partner = get_npc_safe(NPC_PARTNER);
            if (partner == nullptr) {
                return ApiStatus_DONE2;
            }
            partner->pos.x = x;
            partner->pos.y = y;
            partner->pos.z = z;
            partner->colliderPos.x = partner->pos.x;
            partner->colliderPos.y = partner->pos.y;
            partner->colliderPos.z = partner->pos.z;
            partner->flags |= NPC_FLAG_DIRTY_SHADOW;
            break;
        case WHALE_RIDER_KOLORADO:
            kolorado = get_npc_safe(NPC_Kolorado);
            kolorado->pos.x = x;
            kolorado->pos.y = y;
            kolorado->pos.z = z;
            kolorado->colliderPos.x = kolorado->pos.x;
            kolorado->colliderPos.y = kolorado->pos.y;
            kolorado->colliderPos.z = kolorado->pos.z;
            kolorado->flags |= NPC_FLAG_DIRTY_SHADOW;
            break;
    }

    return ApiStatus_BLOCK;
}

// player can press A while riding the whale to make it spout water and toss Mario upward
API_CALLABLE(N(ManageWhaleSpoutPrompt)) {
    u32 buttons = gGameStatusPtr->pressedButtons[0];
    Npc* whaleNpc = get_npc_safe(NPC_Whale);

    switch (N(SpoutState)) {
        case SPOUT_STATE_READY:
            if (buttons & BUTTON_A) {
                N(SpoutState) = SPOUT_STATE_BEGIN;
                break;
            }
            if (N(SpoutInputWindow) >= 150) {
                return ApiStatus_DONE2;
            }
            N(SpoutInputWindow)++;
            break;

        case SPOUT_STATE_BEGIN:
            whaleNpc->curAnim = XNIM_Whale_Spout;
            N(SpoutHeight) = 0.0f;
            N(SpoutVelocity) = 5.0f;
            N(SpoutState) = SPOUT_STATE_RISING;
            break;

        case SPOUT_STATE_RISING:
            N(SpoutHeight) += N(SpoutVelocity);
            if (N(SpoutHeight) < 70.0f) {
                if (N(SpoutVelocity) < 4.0f) {
                    N(SpoutVelocity) = 4.0f;
                }
                N(SpoutVelocity) += 1.0f;
            } else {
                N(SpoutVelocity) -= 2.0f;
            }
            if (whaleNpc->curAnim == XNIM_Whale_Swim) {
                N(SpoutVelocity) = 4.0f;
                N(SpoutState) = SPOUT_STATE_FALLING;
            }
            break;

        case SPOUT_STATE_FALLING:
            N(SpoutHeight) -= N(SpoutVelocity);
            if (N(SpoutHeight) < 0.0f) {
                N(SpoutHeight) = 0.0f;
                return ApiStatus_DONE2;
            }
            N(SpoutVelocity) += 1.0f;
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(N(AwaitSkipScenePrompt)) {
    if(gGameStatusPtr->pressedButtons[0] & BUTTON_B) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript N(EVS_NpcIdle_Whale) = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, mac_06_ENTRY_0)
        Call(GetNpcPos, NPC_Whale, LVar0, LVar1, LVar2)
        Call(NpcFlyTo, NPC_Whale, 50, LVar1, 500, 120, 0, EASING_SIN_OUT)
        Thread
            Call(N(ManageWhaleSpoutPrompt))
        EndThread
        Wait(150)
        Call(SetNpcAnimation, NPC_Whale, XNIM_Whale_Swim)
        Call(NpcFlyTo, NPC_Whale, 500, LVar1, 500, 120, 0, EASING_COS_IN)
        IfEq(GF_StartedChapter5, false)
            Set(GF_StartedChapter5, true)
            Call(FadeOutMusic, 0, 1500)
            Call(GotoMapSpecial, Ref("kmr_22"), kmr_22_ENTRY_5, TRANSITION_BEGIN_OR_END_CHAPTER)
        Else
            Call(GotoMap, Ref("jan_00"), jan_00_ENTRY_0)
        EndIf
    Else
        Call(GetNpcPos, NPC_Whale, LVar0, LVar1, LVar2)
        IfGe(GB_StoryProgress, STORY_CH5_SUSHIE_JOINED_PARTY)
            IfEq(GF_MAC01_Defeated_JrTroopa4, false)
                Call(NpcFlyTo, NPC_Whale, -550, LVar1, 500, 240, 0, EASING_LINEAR)
                Call(SetNpcVar, NPC_JrTroopa, 0, 1)
                Return
            EndIf
        EndIf
        Call(NpcFlyTo, NPC_Whale, -70, LVar1, 500, 120, 0, EASING_SIN_OUT)
        Thread
            Call(N(ManageWhaleSpoutPrompt))
        EndThread
        Wait(150)
        Call(SetNpcAnimation, NPC_Whale, XNIM_Whale_Swim)
        Call(NpcFlyTo, NPC_Whale, -500, LVar1, 500, 120, 0, EASING_COS_IN)
        Call(GotoMap, Ref("mac_05"), mac_05_ENTRY_1)
    EndIf
    Return
    End
};

API_CALLABLE(N(UpdateGullYawInterp)) {
    f32 x1 = evt_get_float_variable(script, LVar1);
    f32 y1 = evt_get_float_variable(script, LVar3);
    f32 x2 = evt_get_float_variable(script, LVar4);
    f32 y2 = evt_get_float_variable(script, LVar5);
    f32 lastYaw = evt_get_float_variable(script, LVar7);
    f32 newYaw, deltaYaw;

    if (evt_get_variable(script, LFlag0)) {
        evt_set_float_variable(script, LVar6, 0.0f);
        evt_set_float_variable(script, LVar7, 0.0f);
        evt_set_variable(script, LFlag0, false);
        evt_set_variable(script, LFlag1, true);
        return ApiStatus_DONE2;
    }

    if (x1 == x2 && y1 == y2) {
        return ApiStatus_DONE2;
    }

    if (evt_get_variable(script, LFlag1)) {
        newYaw = atan2(-x1, y1, -x2, y2);
        evt_set_float_variable(script, LVar6, newYaw);
        evt_set_float_variable(script, LVar7, newYaw);
        evt_set_variable(script, LFlag1, false);
        return ApiStatus_DONE2;
    }

    newYaw = atan2(-x1, y1, -x2, y2);
    newYaw = clamp_angle(newYaw);
    evt_set_float_variable(script, LVar6, newYaw);

    deltaYaw = lastYaw - newYaw;
    if (deltaYaw >= 180.0f) {
        lastYaw -= 360.0f;
    } else if (deltaYaw <= -180.0f) {
        lastYaw += 360.0f;
    }

    evt_set_float_variable(script, LVar7, lastYaw + (f32)((newYaw - lastYaw) * 0.1));
    return ApiStatus_DONE2;
}

API_CALLABLE(N(MakeJrTroopaBubbles)) {
    Npc* jrTroopa = get_npc_safe(NPC_JrTroopa);
    f32 x = jrTroopa->pos.x + 10.0f;
    f32 y = jrTroopa->pos.y;
    f32 z = jrTroopa->pos.z;

    if (y < 0.0f) {
        fx_rising_bubble(0, x, y, z, 0.0f);
        sfx_adjust_env_sound_pos(SOUND_LRAW_JR_TROOPA_SWIM, SOUND_SPACE_DEFAULT, x, y, z);
    }
    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcInit_Whale) = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_HAS_NO_SPRITE, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_HAS_SHADOW, false)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, mac_06_ENTRY_0)
        Call(InterpPlayerYaw, 90, 0)
        Call(InterpNpcYaw, NPC_PARTNER, 90, 0)
        Call(InterpNpcYaw, NPC_Kolorado, 90, 0)
        Call(InterpNpcYaw, NPC_SELF, 90, 0)
        Call(SetNpcPos, NPC_SELF, -300, 0, 500)
    Else
        Call(InterpPlayerYaw, 270, 0)
        Call(InterpNpcYaw, NPC_PARTNER, 270, 0)
        Call(InterpNpcYaw, NPC_Kolorado, 270, 0)
        Call(InterpNpcYaw, NPC_SELF, 270, 0)
        Call(SetNpcPos, NPC_SELF, 300, 0, 500)
    EndIf
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Whale)))
    Call(SetNpcAnimation, NPC_SELF, XNIM_Whale_Swim)
    Call(DisablePlayerPhysics, true)
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, false)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_FLYING | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_ENTITY_COLLISION, true)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Thread
        Call(N(UpdateWhaleRiderPosition), WHALE_RIDER_PLAYER)
    EndThread
    Thread
        Call(N(UpdateWhaleRiderPosition), WHALE_RIDER_PARTNER)
    EndThread
    Thread
        Switch(GB_StoryProgress)
            CaseLt(STORY_CH5_REACHED_LAVA_LAVA_ISLAND)
                Call(N(UpdateWhaleRiderPosition), WHALE_RIDER_KOLORADO)
            CaseEq(STORY_CH5_TRADED_VASE_FOR_SEED)
                Call(N(UpdateWhaleRiderPosition), WHALE_RIDER_KOLORADO)
        EndSwitch
    EndThread
    IfLt(GB_StoryProgress, STORY_CH5_REACHED_LAVA_LAVA_ISLAND)
        Return
    EndIf
    IfGe(GB_StoryProgress, STORY_CH5_SUSHIE_JOINED_PARTY)
        IfEq(GF_MAC01_Defeated_JrTroopa4, false)
            Return
        EndIf
    EndIf
    Thread
        Call(N(AwaitSkipScenePrompt))
        Call(GetEntryID, LVar0)
        IfEq(LVar0, mac_06_ENTRY_0)
            Call(GotoMap, Ref("jan_00"), jan_00_ENTRY_0)
        Else
            Call(GotoMap, Ref("mac_05"), mac_05_ENTRY_1)
        EndIf
    EndThread
    Return
    End
};

EvtScript N(EVS_NpcInit_Kolorado) = {
    Return
    End
};

Vec3f N(FlightPath)[] = {
    { -332.0,    50.0,  120.0 },
    { -160.0,    70.0,  300.0 },
    {  -71.0,    80.0,  130.0 },
    {  105.0,    90.0,  262.0 },
    {  221.0,   100.0,  120.0 },
    {  404.0,    85.0,  150.0 },
    {  238.0,    70.0,  -57.0 },
    {   63.0,    70.0,  -42.0 },
    { -131.0,    60.0,  144.0 },
    {  -75.0,   100.0,  -60.0 },
    {  200.0,    60.0, -300.0 },
    {   20.0,    60.0, -280.0 },
    {   70.0,    60.0,   80.0 },
    { -332.0,    50.0,  120.0 },
};

EvtScript N(EVS_FlyingGull) = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(CloneModel, MODEL_hontai, CLONED_MODEL_GULL)
    Set(LFlag0, true)
    Set(LFlag1, false)
    SetF(LVar7, 0)
    Label(10)
        Call(LoadPath, 500, Ref(N(FlightPath)), ARRAY_COUNT(N(FlightPath)), EASING_LINEAR)
        Label(0)
            Call(GetNextPathPos)
            Call(TranslateModel, MODEL_hontai, LVar1, LVar2, LVar3)
            SetF(LVar8, LVar2)
            MulF(LVar8, -1)
            Call(TranslateModel, CLONED_MODEL_GULL, LVar1, LVar8, LVar3)
            Call(N(UpdateGullYawInterp))
            Call(RotateModel, MODEL_hontai, LVar7, 0, 1, 0)
            Call(RotateModel, CLONED_MODEL_GULL, LVar7, 0, 1, 0)
            Call(RotateModel, CLONED_MODEL_GULL, 180, 0, 0, 1)
            Set(LVar4, LVar1)
            Set(LVar5, LVar3)
            Wait(1)
            IfEq(LVar0, 1)
                Goto(0)
            EndIf
        Goto(10)
    Return
    End
};

EvtScript N(EVS_NpcIdle_JrTroopa) = {
    Call(SetSelfVar, 0, 0)
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfNe(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(60)
    Call(SetMusic, 0, SONG_JR_TROOPA_THEME, 0, VOL_LEVEL_FULL)
    Call(PlaySound, SOUND_LOOP_JR_TROOPA_SWIM)
    Call(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_ChargeTripped)
    Call(SetNpcPos, NPC_SELF, 250, -30, 500)
    Wait(5)
    ChildThread
        Loop(0)
            Call(N(MakeJrTroopaBubbles))
            Wait(5)
        EndLoop
    EndChildThread
    Call(SetNpcSpeed, NPC_SELF, Float(2.0))
    Call(NpcMoveTo, NPC_SELF, -300, 500, 0)
    Call(GotoMap, Ref("mac_05"), mac_05_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_NpcInit_JrTroopa) = {
    IfGe(GB_StoryProgress, STORY_CH5_SUSHIE_JOINED_PARTY)
        IfEq(GF_MAC01_Defeated_JrTroopa4, false)
            Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_JrTroopa)))
            Return
        EndIf
    EndIf
    Call(RemoveNpc, NPC_SELF)
    Return
    End
};

NpcData N(NpcData_Whale) = {
    .id = NPC_Whale,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Whale),
    .settings = &N(NpcSettings_Whale),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = WHALE_ANIMS,
};

NpcData N(NpcData_Kolorado) = {
    .id = NPC_Kolorado,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Kolorado),
    .settings = &N(NpcSettings_Kolorado),
    .flags = COMMON_PASSIVE_FLAGS,
    .drops = NO_DROPS,
    .animations = KOLORADO_ANIMS,
};

AnimID N(LimitAnims_JrTroopa)[] = {
    ANIM_JrTroopa_Still,
    ANIM_JrTroopa_Idle,
    ANIM_JrTroopa_ChargeTripped,
    ANIM_LIST_END
};

NpcData N(NpcData_JrTroopa) = {
    .id = NPC_JrTroopa,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &N(EVS_NpcInit_JrTroopa),
    .settings = &N(NpcSettings_JrTroopa),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = NO_DROPS,
    .animations = JR_TROOPA_ANIMS,
    .limitAnimations = N(LimitAnims_JrTroopa),
    .tattle = MSG_NpcTattle_JrTroopa,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_JrTroopa)),
    NPC_GROUP(N(NpcData_Whale)),
    NPC_GROUP(N(NpcData_Kolorado)),
    {}
};
