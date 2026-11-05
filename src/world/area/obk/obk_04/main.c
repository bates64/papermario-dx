#include "obk_04.h"
#include "effects.h"

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Basement.index)
            Thread
                Wait(10)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetPlayerSpeed, 3.0)
                Call(PlayerMoveTo, -150, LVar2, 0)
            EndThread
            Call(EnableModel, MODEL_door_off1, false)
            Call(EnableModel, MODEL_door_off2, false)
            Set(LVar2, MODEL_door1)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
            Call(EnableModel, MODEL_door_off1, true)
            Call(EnableModel, MODEL_door_off2, true)
            Wait(20)
            Call(MakeLerp, 0, -90, 15, EASING_QUADRATIC_IN)
            Loop(0)
                Call(UpdateLerp)
                Call(RotateModel, MODEL_door1, LVar0, 0, 0, 1)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_1.pos.x, $LandingDustPos_1.pos.y, $LandingDustPos_1.pos.z, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_2.pos.x, $LandingDustPos_2.pos.y, $LandingDustPos_2.pos.z, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_3.pos.x, $LandingDustPos_3.pos.y, $LandingDustPos_3.pos.z, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_4.pos.x, $LandingDustPos_4.pos.y, $LandingDustPos_4.pos.z, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_5.pos.x, $LandingDustPos_5.pos.y, $LandingDustPos_5.pos.z, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_6.pos.x, $LandingDustPos_6.pos.y, $LandingDustPos_6.pos.z, 0)
            Wait(20)
            Call(EnableModel, MODEL_door1, false)
            Call(MakeLerp, 0, 10, 15, EASING_LINEAR)
            Loop(0)
                Call(UpdateLerp)
                Call(TranslateModel, MODEL_door_off1, LVar0, 0, 0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(EnableModel, MODEL_door_off3, false)
    EndSwitch
    Return
    End
};

EvtScript EVS_SetupTexPan = {
    // spooky fog
    Call(SetTexPanner, MODEL_m1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(  300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_ManageHole)
    Exec(EVS_SetupTexPan)
    Exec(EVS_EnterMap)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_hip1, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_SetupMusic)
    Return
    End
};
