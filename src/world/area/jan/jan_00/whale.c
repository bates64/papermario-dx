#include "jan_00.h"
#include "effects.h"

#include "world/common/atomic/WhaleAnim.inc.c"

API_CALLABLE(N(GetWhaleHeadPos)) {
    Npc* whale = get_npc_safe(NPC_Whale);
    f32 yaw = -whale->yaw;
    f32 x = whale->pos.x + 30.0f + (sin_deg(yaw) * 170.0f);
    f32 z = whale->pos.z + (cos_deg(yaw) * 170.0f);
    f32 y = whale->pos.y + 50.0f;

    evt_set_float_variable(script, LVar0, x);
    evt_set_float_variable(script, LVar1, y);
    evt_set_float_variable(script, LVar2, z);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_WhaleState_Still) = {
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, MODEL_o167, LVar0, 1, 0, 0)
    Call(RotateModel, MODEL_o168, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Yell) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, 30, 30, 1, 0)
    SetF(LVar1, LVar0)
    DivF(LVar1, Float(3.0))
    Call(RotateModel, MODEL_o173, LVar0, 0, 0, 1)
    Call(RotateGroup, MODEL_dou, LVar1, 0, 0, -1)
    Call(TranslateModel, MODEL_o170, -5, -68, 0)
    Call(TranslateModel, MODEL_o183, -5, -68, 0)
    Call(TranslateModel, MODEL_o167, 60, 29, -51)
    Call(TranslateModel, MODEL_o168, 60, 29, 51)
    Call(RotateModel, MODEL_o170, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o183, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o167, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o168, LVar1, 0, 0, -1)
    Call(TranslateModel, MODEL_o170, 5, 68, 0)
    Call(TranslateModel, MODEL_o183, 5, 68, 0)
    Call(TranslateModel, MODEL_o167, -60, -29, 51)
    Call(TranslateModel, MODEL_o168, -60, -29, -51)
    Call(CosInterpMinMax, LVarC, LVar0, 0, -40, 30, 1, 0)
    Call(TranslateModel, MODEL_bero, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_IdleSad) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, -30, 8, 1, 0)
    AddF(LVar0, Float(30.0))
    SetF(LVar1, LVar0)
    DivF(LVar1, Float(3.0))
    Call(RotateModel, MODEL_o173, LVar0, 0, 0, 1)
    Call(RotateGroup, MODEL_dou, LVar1, 0, 0, -1)
    Call(TranslateModel, MODEL_o170, -5, -68, 0)
    Call(TranslateModel, MODEL_o183, -5, -68, 0)
    Call(TranslateModel, MODEL_o167, 60, 29, -51)
    Call(TranslateModel, MODEL_o168, 60, 29, 51)
    Call(RotateModel, MODEL_o170, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o183, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o167, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o168, LVar1, 0, 0, -1)
    Call(TranslateModel, MODEL_o170, 5, 68, 0)
    Call(TranslateModel, MODEL_o183, 5, 68, 0)
    Call(TranslateModel, MODEL_o167, -60, -29, 51)
    Call(TranslateModel, MODEL_o168, -60, -29, -51)
    Call(CosInterpMinMax, LVarC, LVar0, 0, -40, 120, 1, 0)
    Call(TranslateModel, MODEL_bero, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_WalkSad) = {
    Return
    End
};

EvtScript N(EVS_WhaleState_Shout) = {
    Set(LVar1, LVarC)
    Mod(LVar1, 4)
    IfEq(LVar1, 0)
        Call(N(GetWhaleHeadPos))
        PlayEffect(EFFECT_DAMAGE_STARS, FX_DAMAGE_STARS_2, LVar0, LVar1, LVar2, 0, -1, 0, 5)
    EndIf
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, MODEL_o167, LVar0, 1, 0, 0)
    Call(RotateModel, MODEL_o168, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_TalkSad) = {
    Return
    End
};

EvtScript N(EVS_WhaleState_HurtStill) = {
    IfGe(LVarC, 0)
        IfLe(LVarC, 2)
            Call(EnableModel, MODEL_o170, false)
            Call(EnableModel, MODEL_o183, true)
            Return
        EndIf
    EndIf
    IfEq(LVarC, 15)
        Call(EnableModel, MODEL_o170, false)
        Call(EnableModel, MODEL_o183, true)
        Return
    EndIf
    IfEq(LVarC, 22)
        Call(EnableModel, MODEL_o170, false)
        Call(EnableModel, MODEL_o183, true)
        Return
    EndIf
    Call(EnableModel, MODEL_o170, true)
    Call(EnableModel, MODEL_o183, false)
    Return
    End
};

EvtScript N(EVS_WhaleState_Run) = {
    Set(LVar0, LVarC)
    Div(LVar0, 20)
    Mod(LVar0, 2)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(CosInterpMinMax, LVarC, LVar0, Float(-1.0), Float(1.0), 3, 0, 0)
    Call(TranslateModel, MODEL_o173, LVar0, 0, 0)
    Call(TranslateGroup, MODEL_dou, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o170, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o183, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o167, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o168, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o167, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o168, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Panic) = {
    Call(CosInterpMinMax, LVarC, LVar0, Float(-6.0), Float(6.0), 3, 0, 0)
    Call(CosInterpMinMax, LVarC, LVar1, Float(6.0), Float(-6.0), 2, 0, 0)
    Call(TranslateModel, MODEL_o173, LVar0, LVar1, 0)
    Call(TranslateGroup, MODEL_dou, LVar0, LVar1, 0)
    Call(TranslateModel, MODEL_o170, LVar0, LVar1, 0)
    Call(TranslateModel, MODEL_o183, LVar0, LVar1, 0)
    Call(TranslateModel, MODEL_o167, LVar0, LVar1, 0)
    Call(TranslateModel, MODEL_o168, LVar0, LVar1, 0)
    Call(TranslateModel, MODEL_o167, LVar0, LVar1, 0)
    Call(TranslateModel, MODEL_o168, LVar0, LVar1, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Talk) = {
    Set(LVar0, LVarC)
    Div(LVar0, 20)
    Mod(LVar0, 2)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(CosInterpMinMax, LVarC, LVar0, Float(-1.0), Float(1.0), 3, 0, 0)
    Call(TranslateModel, MODEL_o173, LVar0, 0, 0)
    Call(TranslateGroup, MODEL_dou, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o170, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o183, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o167, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o168, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o167, LVar0, 0, 0)
    Call(TranslateModel, MODEL_o168, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Idle) = {
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, MODEL_o167, LVar0, 1, 0, 0)
    Call(RotateModel, MODEL_o168, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Walk) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, 8, 3, 0, 0)
    Set(LVar1, LVar0)
    Div(LVar1, 3)
    Call(RotateModel, MODEL_o173, LVar0, 0, 0, 1)
    Call(RotateGroup, MODEL_dou, LVar1, 0, 0, -1)
    Call(TranslateModel, MODEL_o170, -5, -68, 0)
    Call(TranslateModel, MODEL_o183, -5, -68, 0)
    Call(TranslateModel, MODEL_o167, 60, 29, -51)
    Call(TranslateModel, MODEL_o168, 60, 29, 51)
    Call(RotateModel, MODEL_o170, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o183, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o167, LVar1, 0, 0, -1)
    Call(RotateModel, MODEL_o168, LVar1, 0, 0, -1)
    Call(TranslateModel, MODEL_o170, 5, 68, 0)
    Call(TranslateModel, MODEL_o183, 5, 68, 0)
    Call(TranslateModel, MODEL_o167, -60, -29, 51)
    Call(TranslateModel, MODEL_o168, -60, -29, -51)
    Set(LVar0, LVarC)
    Mul(LVar0, 2)
    Call(CosInterpMinMax, LVar0, LVar0, 30, 60, 3, 0, 0)
    Call(RotateModel, MODEL_o167, LVar0, 1, 0, 0)
    Call(RotateModel, MODEL_o168, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_SetupWhale) = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(MakeLocalVertexCopy, VTX_COPY_1, MODEL_karada, true)
    Call(SetCustomGfxBuilders, CUSTOM_GFX_1, Ref(N(build_gfx_whale_body)), nullptr)
    Call(SetModelCustomGfx, MODEL_karada, CUSTOM_GFX_1, -1)
    Call(MakeLocalVertexCopy, VTX_COPY_2, MODEL_onaka, true)
    Call(SetCustomGfxBuilders, CUSTOM_GFX_2, Ref(N(build_gfx_whale_belly)), nullptr)
    Call(SetModelCustomGfx, MODEL_onaka, CUSTOM_GFX_2, -1)
    Thread
        Label(0)
        Call(N(MakeWhaleRootPos), NPC_Whale, LVar0, LVar1, LVar2)
        SubF(LVar0, -80)
        SubF(LVar1, -18)
        SubF(LVar2, 420)
        AddF(LVar0, 55)
        AddF(LVar1, -20)
        AddF(LVar2, 0)
        Call(TranslateModel, MODEL_bero, LVar0, LVar1, LVar2)
        Call(TranslateModel, MODEL_o170, LVar0, LVar1, LVar2)
        Call(TranslateModel, MODEL_o183, LVar0, LVar1, LVar2)
        Call(TranslateModel, MODEL_o173, LVar0, LVar1, LVar2)
        Call(TranslateModel, MODEL_o167, LVar0, LVar1, LVar2)
        Call(TranslateModel, MODEL_o168, LVar0, LVar1, LVar2)
        Call(TranslateGroup, MODEL_dou, LVar0, LVar1, LVar2)
        Call(GetNpcYaw, NPC_Whale, LVar0)
        MulF(LVar0, -1)
        AddF(LVar0, -90)
        Call(TranslateModel, MODEL_bero, -100, 0, 0)
        Call(TranslateModel, MODEL_o170, -100, 0, 0)
        Call(TranslateModel, MODEL_o183, -100, 0, 0)
        Call(TranslateModel, MODEL_o173, -100, 0, 0)
        Call(TranslateModel, MODEL_o167, -100, 0, 0)
        Call(TranslateModel, MODEL_o168, -100, 0, 0)
        Call(TranslateGroup, MODEL_dou, -100, 0, 0)
        Call(TranslateModel, MODEL_bero, 100, -1, 0)
        Call(TranslateModel, MODEL_o170, -5, -68, 0)
        Call(TranslateModel, MODEL_o183, -5, -68, 0)
        Call(TranslateModel, MODEL_o173, 102, 4, 0)
        Call(TranslateModel, MODEL_o167, 60, 29, -51)
        Call(TranslateModel, MODEL_o168, 60, 29, 51)
        Call(RotateModel, MODEL_bero, LVar0, 0, 1, 0)
        Call(RotateModel, MODEL_o170, LVar0, 0, 1, 0)
        Call(RotateModel, MODEL_o183, LVar0, 0, 1, 0)
        Call(RotateModel, MODEL_o173, LVar0, 0, 1, 0)
        Call(RotateModel, MODEL_o167, LVar0, 0, 1, 0)
        Call(RotateModel, MODEL_o168, LVar0, 0, 1, 0)
        Call(RotateGroup, MODEL_dou, LVar0, 0, 1, 0)
        Call(TranslateModel, MODEL_bero, -100, 1, 0)
        Call(TranslateModel, MODEL_o170, 5, 68, 0)
        Call(TranslateModel, MODEL_o183, 5, 68, 0)
        Call(TranslateModel, MODEL_o173, -102, -4, 0)
        Call(TranslateModel, MODEL_o167, -60, -29, 51)
        Call(TranslateModel, MODEL_o168, -60, -29, -51)
        Call(TranslateModel, MODEL_bero, 100, 0, 0)
        Call(TranslateModel, MODEL_o170, 100, 0, 0)
        Call(TranslateModel, MODEL_o183, 100, 0, 0)
        Call(TranslateModel, MODEL_o173, 100, 0, 0)
        Call(TranslateModel, MODEL_o167, 100, 0, 0)
        Call(TranslateModel, MODEL_o168, 100, 0, 0)
        Call(TranslateGroup, MODEL_dou, 100, 0, 0)
        Call(GetNpcAnimation, NPC_Whale, LVar0)
        IfNe(LVar0, LVarB)
            Set(LVarB, LVar0)
            Set(LVarC, 0)
            Call(EnableModel, MODEL_o170, true)
            Call(EnableModel, MODEL_o183, false)
            Switch(LVarB)
                CaseEq(ANIM_Kolorado_IdleSad)
                    Set(LVarD, Ref(N(EVS_WhaleState_IdleSad)))
                CaseEq(ANIM_Kolorado_Still)
                    Set(LVarD, Ref(N(EVS_WhaleState_Still)))
                CaseEq(ANIM_Kolorado_Yell)
                    Set(LVarD, Ref(N(EVS_WhaleState_Yell)))
                CaseEq(ANIM_Kolorado_Idle)
                    Set(LVarD, Ref(N(EVS_WhaleState_Idle)))
                CaseEq(ANIM_Kolorado_Walk)
                    Set(LVarD, Ref(N(EVS_WhaleState_Walk)))
                CaseEq(ANIM_Kolorado_WalkSad)
                    Set(LVarD, Ref(N(EVS_WhaleState_WalkSad)))
                    Call(EnableModel, MODEL_o170, false)
                    Call(EnableModel, MODEL_o183, false)
                CaseEq(ANIM_Kolorado_Run)
                    Set(LVarD, Ref(N(EVS_WhaleState_Run)))
                    Call(EnableModel, MODEL_o170, false)
                    Call(EnableModel, MODEL_o183, false)
                CaseEq(ANIM_Kolorado_Panic)
                    Set(LVarD, Ref(N(EVS_WhaleState_Panic)))
                    Call(EnableModel, MODEL_o170, false)
                    Call(EnableModel, MODEL_o183, false)
                CaseEq(ANIM_Kolorado_Talk)
                    Set(LVarD, Ref(N(EVS_WhaleState_Talk)))
                CaseEq(ANIM_Kolorado_Shout)
                    Set(LVarD, Ref(N(EVS_WhaleState_Shout)))
                CaseEq(ANIM_Kolorado_TalkSad)
                    Set(LVarD, Ref(N(EVS_WhaleState_TalkSad)))
                CaseEq(ANIM_Kolorado_HurtStill)
                    Set(LVarD, Ref(N(EVS_WhaleState_HurtStill)))
            EndSwitch
        EndIf
        ExecWait(LVarD)
        Add(LVarC, 1)
        IfGt(LVarC, 1000)
            Set(LVarC, 0)
        EndIf
        Goto(0)
    EndThread
    Return
    End
};

EvtScript N(EVS_SetWhaleIdleSad) = {
    Call(SetNpcAnimation, NPC_Whale, ANIM_Kolorado_IdleSad)
    Return
    End
};
