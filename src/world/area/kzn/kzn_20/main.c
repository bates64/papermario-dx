#include "kzn_20.h"
#include "world/area/kzn/kzn_19.h"
#include "world/area/kzn/kzn_22.h"
#include "effects.h"

EvtScript EVS_ExitWalk_kzn_19_2 = EVT_EXIT_WALK(60, $Kzn19, $kzn_19.Kzn20);
EvtScript EVS_ExitWalk_kzn_22_0 = EVT_EXIT_WALK(60, $Kzn22, $kzn_22.Kzn20);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_19_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_22_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_UpdateTexPan_Lava = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTexPanner, MODEL_yu, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -700,  700,  200, -300)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o919, .pos = $LavaReset_o919.pos },
    { .colliderID = COLLIDER_o870, .pos = $LavaReset_o870.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_DetermineLavaLevel = {
    Loop(0)
        IfGe(GB_StoryProgress, STORY_CH5_OPENED_ESCAPE_ROUTE)
            Label(1)
                IfLt(MV_LavaPosOffset, 110)
                    SubF(MV_WaveScaleOffset, 0.01)
                    AddF(MV_PosScaleCoeff, 0.01)
                    Loop(5)
                        AddF(MV_LavaPosOffset, 0.75)
                        Wait(9)
                    EndLoop
                Else
                    BreakLoop
                EndIf
                Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_InterruptPartnersInLava = {
    Loop(0)
        Loop(0)
            Wait(1)
            Call(GetModelCenter, MODEL_yu)
            Call(GetPlayerPos, LVar0, LVar3, LVar2)
            IfLt(LVar3, LVar1)
                BreakLoop
            EndIf
        EndLoop
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, PARTNER_LAKILESTER)
            Call(InterruptUsePartner)
            Call(SetPlayerActionState, ACTION_STATE_HIT_LAVA)
            Wait(30)
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_UpdateLavaWaves = {
    SetGroup(EVT_GROUP_NOT_BATTLE)
    Call(EnableModel, MODEL_yu, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_yu, COLLIDER_FLAGS_UPPER_MASK)
    Call(ParentColliderToModel, COLLIDER_yu, MODEL_yu)
    Label(0)
        IfEq(AF_KZN_RumblingIntensified, false)
            Wait(1)
            Goto(0)
        EndIf
    Call(EnableModel, MODEL_yu, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS,  COLLIDER_yu, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_yu, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    IfLt(GB_StoryProgress, STORY_CH5_OPENED_ESCAPE_ROUTE)
        SetF(MV_LavaPosOffset, 35)
        SetF(MV_WaveScaleOffset, 1.2)
        SetF(MV_PosScaleCoeff, -1.2)
    Else
        SetF(MV_LavaPosOffset, 110)
        SetF(MV_WaveScaleOffset, 1.0)
        SetF(MV_PosScaleCoeff, -1.0)
    EndIf
    Exec(EVS_DetermineLavaLevel)
    Exec(EVS_InterruptPartnersInLava)
    Loop(0)
        Call(MakeLerp, 0, 260, 30, EASING_COS_IN)
        Loop(0)
            Call(UpdateLerp)
            DivF(LVar0, 100.0)
            SubF(LVar0, MV_WaveScaleOffset)
            SetF(LVar3, MV_LavaPosOffset)
            SetF(LVar4, MV_LavaPosOffset)
            DivF(LVar3, MV_PosScaleCoeff)
            MulF(LVar3, LVar0)
            AddF(LVar4, LVar3) // = PosOffset + Scale * (PosOffset / PosScaleCoeff)
            Call(TranslateModel, MODEL_yu, 0, LVar4, 0)
            Call(ScaleModel, MODEL_yu, 1, LVar0, 1)
            Call(TranslateModel, MODEL_yu, 0, MV_LavaPosOffset, 0)
            Call(UpdateColliderTransform, COLLIDER_yu)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 260, 0, 60, EASING_SIN_OUT)
        Loop(0)
            Call(UpdateLerp)
            DivF(LVar0, 100.0)
            SubF(LVar0, MV_WaveScaleOffset)
            SetF(LVar3, MV_LavaPosOffset)
            SetF(LVar4, MV_LavaPosOffset)
            DivF(LVar3, MV_PosScaleCoeff)
            MulF(LVar3, LVar0)
            AddF(LVar4, LVar3)
            Call(TranslateModel, MODEL_yu, 0, LVar4, 0)
            Call(ScaleModel, MODEL_yu, 1, LVar0, 1)
            Call(TranslateModel, MODEL_yu, 0, MV_LavaPosOffset, 0)
            Call(UpdateColliderTransform, COLLIDER_yu)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndLoop
    Return
    End
};

BombTrigger WeakWallBombTrigger = {
    .pos = $BombPos_WeakWallBombTrigger.pos,
    .diameter = 2.0f * $BombPos_WeakWallBombTrigger.radius,
};

EvtScript EVS_OnBreakWall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Call(EnableGroup, MODEL_bom_mae, false)
    Call(EnableGroup, MODEL_bom_ato, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    Set(GB_StoryProgress, STORY_CH5_OPENED_ESCAPE_ROUTE)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_ShakingWorld)
    IfLt(GB_StoryProgress, STORY_CH5_OPENED_ESCAPE_ROUTE)
        Call(EnableGroup, MODEL_bom_ato, false)
        BindTrigger(EVS_OnBreakWall, TRIGGER_POINT_BOMB, WeakWallBombTrigger, 1, 0)
    Else
        Call(EnableGroup, MODEL_bom_mae, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_UpdateLavaWaves)
    Exec(EVS_UpdateTexPan_Lava)
    Return
    End
};
