#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/hos_02_shape.h"

EvtScript EVS_PreBattle = {
    Thread
        Call(SetTexPanner, MODEL_o372, TEX_PANNER_1)
        Call(SetTexPanner, MODEL_o375, TEX_PANNER_1)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Loop(0)
            Add(LVar0, -50)
            Add(LVar1, 300)
            Add(LVar2, 90)
            Add(LVar3, -200)
            Call(SetTexPanOffset, TEX_PANNER_1, TEX_PANNER_MAIN, LVar0, LVar1)
            Call(SetTexPanOffset, TEX_PANNER_1, TEX_PANNER_AUX, LVar2, LVar3)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Set(LVarA, 0)
        Label(2)
            Call(MakeLerp, -7, 7, 40, EASING_COS_IN_OUT)
            Label(0)
                Call(UpdateLerp)
                Call(TranslateModel, MODEL_o371, 0, LVar0, 0)
                Call(TranslateModel, MODEL_o372, 0, LVar0, 0)
                Mul(LVar0, 3)
                Call(RotateModel, MODEL_o371, LVarA, 0, 0, 1)
                Add(LVarA, -3)
                Call(ClampAngleFloat, LVarA)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(0)
                EndIf
            Call(MakeLerp, 7, -7, 40, EASING_COS_IN_OUT)
            Label(1)
                Call(UpdateLerp)
                Call(TranslateModel, MODEL_o371, 0, LVar0, 0)
                Call(TranslateModel, MODEL_o372, 0, LVar0, 0)
                Mul(LVar0, 3)
                Call(RotateModel, MODEL_o371, LVarA, 0, 0, 1)
                Add(LVarA, -3)
                Call(ClampAngleFloat, LVarA)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(1)
                EndIf
            Goto(2)
    EndThread
    Thread
        Set(LVarA, 0)
        Label(2)
            Call(MakeLerp, -10, 4, 40, EASING_COS_IN_OUT)
            Label(0)
                Call(UpdateLerp)
                Call(TranslateModel, MODEL_o376, 0, LVar0, 0)
                Call(TranslateModel, MODEL_o375, 0, LVar0, 0)
                Mul(LVar0, -3)
                Call(RotateModel, MODEL_o376, LVarA, 0, 0, 1)
                Add(LVarA, -3)
                Call(ClampAngleFloat, LVarA)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(0)
                EndIf
            Call(MakeLerp, 4, -10, 40, EASING_COS_IN_OUT)
            Label(1)
                Call(UpdateLerp)
                Call(TranslateModel, MODEL_o376, 0, LVar0, 0)
                Call(TranslateModel, MODEL_o375, 0, LVar0, 0)
                Mul(LVar0, -3)
                Call(RotateModel, MODEL_o376, LVarA, 0, 0, 1)
                Add(LVarA, -3)
                Call(ClampAngleFloat, LVarA)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(1)
                EndIf
            Goto(2)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "hos_tex",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
