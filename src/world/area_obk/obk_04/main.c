#include "obk_04.h"
#include "effects.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(obk_04_ENTRY_0)
            Thread
                Wait(10)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetPlayerSpeed, Float(3.0))
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
            PlayEffect(EFFECT_LANDING_DUST, 1, -215, 0, 25, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, -215, 0, -25, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, -200, 0, 25, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, -200, 0, -25, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, -185, 0, 25, 0)
            PlayEffect(EFFECT_LANDING_DUST, 1, -185, 0, -25, 0)
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

EvtScript N(EVS_SetupTexPan) = {
    // spooky fog
    Call(SetTexPanner, MODEL_m1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(  300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    SetUP_CAMERA_NO_LEAD()
    Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_ManageHole))
    Exec(N(EVS_SetupTexPan))
    Exec(N(EVS_EnterMap))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_hip1, COLLIDER_FLAGS_UPPER_MASK)
    Exec(N(EVS_SetupMusic))
    Return
    End
};
