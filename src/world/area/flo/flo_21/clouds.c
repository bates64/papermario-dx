#include "flo_21.h"

EvtScript EVS_SetupCloudPuffs = {
    Thread
        Set(LVarF, 0)
        Label(0)
            Call(CosInterpMinMax, LVarF, LVar0, 0.968, 1.031, 15, 0, 0)
            Call(CosInterpMinMax, LVarF, LVar1, 1.031, 0.968, 15, 0, 0)
            Call(ScaleModel, MODEL_o1, LVar1, LVar0, 1)
            Call(ScaleModel, MODEL_o2, LVar1, LVar0, 1)
            Call(ScaleModel, MODEL_o3, LVar0, LVar1, 1)
            Call(ScaleModel, MODEL_o4, LVar0, LVar1, 1)
            Call(ScaleModel, MODEL_o9, LVar0, LVar1, 1)
            Call(ScaleModel, MODEL_o14, LVar1, LVar0, 1)
            Call(ScaleModel, MODEL_o15, LVar0, LVar1, 1)
            Call(ScaleModel, MODEL_o16, LVar0, LVar1, 1)
            Add(LVarF, 1)
            IfGe(LVarF, 30)
                Set(LVarF, 0)
            EndIf
            Wait(1)
            Goto(0)
    EndThread
    Return
    End
};
