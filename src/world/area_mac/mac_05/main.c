#include "mac_05.h"

#include "world/common/atomic/TexturePan.inc.c"

API_CALLABLE(N(WaveScaleInterp)) {
    Bytecode* args = script->ptrReadPos;
    s32 tvar = *args++;
    s32 time = evt_get_variable(script, tvar);
    s32 out = *args++;
    f32 min = evt_get_float_variable(script, *args++);
    f32 max = evt_get_float_variable(script, *args++);
    s32 period = evt_get_variable(script, *args++);
    b32 oneshot = evt_get_variable(script, *args++);
    f32 phase = evt_get_float_variable(script, *args++);
    f32 diff = (max - min) / 2;

    if (oneshot && period < time) {
        time = period;
        evt_set_variable(script, tvar, period);
    }

    evt_set_float_variable(script, out, (min + diff) - (diff * cos_deg(((time * 180.0f) / period) + phase)));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_AnimateWaves) = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Set(LVarC, 0)
    Label(0)
        IfGe(LVarC, 60)
            Set(LVarC, 0)
        EndIf
        Call(N(WaveScaleInterp), LVarC, LVar0, Float(-1.0), Float(1.0), 30, false, 0)
        Call(ScaleModel, MODEL_kaimen, 1, LVar0, 1)
        Add(LVarC, 1)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript N(EVS_AnimateFish) = {
    Loop(0)
        Call(MakeLerp, 600, -240, 320, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, MODEL_o177, LVar0, -25, -75)
            Call(RotateModel, MODEL_o177, 0, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, -240, 600, 320, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, MODEL_o177, LVar0, -25, -75)
            Call(RotateModel, MODEL_o177, 180, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndLoop
    Return
    End
};

EvtScript N(EVS_ExitWalk_mac_04_1) = EVT_EXIT_WALK(60, mac_05_ENTRY_0, "mac_04", mac_04_ENTRY_1);

EvtScript N(EVS_ExitWalk_kgr_01_0) = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, mac_05_ENTRY_3)
    Exec(ExitWalk)
    Set(GB_StoryProgress, STORY_CH5_ENTERED_WHALE)
    Call(GotoMap, Ref("kgr_01"), kgr_01_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_mac_04_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_kgr_01_0)), TRIGGER_FLOOR_TOUCH, COLLIDER_deilit9, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(N(EVS_BindExitTriggers))
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(mac_05_ENTRY_0)
            Set(LVar0, Ref(N(EVS_BindExitTriggers)))
            Exec(EnterWalk)
        CaseEq(mac_05_ENTRY_1)
            Exec(N(EVS_802496FC))
            Exec(N(EVS_BindExitTriggers))
        CaseEq(mac_05_ENTRY_2)
            Exec(N(EVS_80248878))
            Exec(N(EVS_BindExitTriggers))
        CaseEq(mac_05_ENTRY_3)
            Call(DisablePlayerInput, true)
            Call(DisablePlayerPhysics, true)
            Call(SetPlayerPos, -160, -10, 371)
            Call(SetNpcPos, NPC_PARTNER, -160, -10, 371)
            Call(SetEnemyFlagBits, NPC_Whale, ENEMY_FLAG_CANT_INTERACT, true)
            Call(DisablePartnerAI, 0)
            Call(InterruptUsePartner)
            Wait(10)
            Thread
                Call(MakeLerp, -160, -220, 30, EASING_LINEAR)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetPlayerPos, LVar0, -10, 371)
                    Call(SetNpcPos, NPC_PARTNER, LVar0, -10, 371)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
            EndThread
            Call(SetNpcAnimation, NPC_Whale, ANIM_Kolorado_Yell)
            Wait(30)
            Call(SetPlayerPos, -280, -10, 371)
            Call(EnablePartnerAI)
            Call(DisablePlayerPhysics, false)
            Call(DisablePlayerInput, false)
            Set(LVar0, Ref(N(EVS_BindExitTriggers)))
            ExecWait(EnterWalk)
            Call(SetNpcPos, NPC_Whale, -220, 10, 372)
            Call(SetEnemyFlagBits, NPC_Whale, ENEMY_FLAG_CANT_INTERACT, false)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH4_STAR_SPRIT_DEPARTED)
            Set(LVar0, Ref(N(NpcSetA)))
        CaseLt(STORY_CH5_REACHED_LAVA_LAVA_ISLAND)
            Set(LVar0, Ref(N(NpcSetB)))
        CaseLt(STORY_CH5_RETURNED_TO_TOAD_TOWN)
            Call(GetEntryID, LVar1)
            IfEq(LVar1, mac_05_ENTRY_1)
                IfEq(GF_MAC01_Defeated_JrTroopa4, false)
                    Set(LVar0, Ref(N(NpcSetC)))
                Else
                    Set(LVar0, Ref(N(NpcSetB)))
                EndIf
            Else
                Set(LVar0, Ref(N(NpcSetA)))
            EndIf
        CaseLt(STORY_CH6_BEGAN_PEACH_MISSION)
            Set(LVar0, Ref(N(NpcSetA)))
        CaseDefault
            Set(LVar0, Ref(N(NpcSetA)))
    EndSwitch
    Call(MakeNpcs, false, LVar0)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupWhale))
    Call(GetEntryID, LVar0)
    Exec(N(EVS_SetupRooms))
    Exec(N(EVS_SetupMusic))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitne, COLLIDER_FLAGS_UPPER_MASK)
    Exec(N(EVS_EnterMap))
    Wait(1)
    Exec(N(EVS_AnimateWaves))
    Call(SetTexPanner, MODEL_kaimen, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  100,  100,  -70,  -50)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Exec(N(EVS_AnimateFish))
    Exec(N(EVS_AnimateClub64Sign))
    Return
    End
};
