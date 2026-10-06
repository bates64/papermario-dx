#include "common.h"

EvtScript EVS_UseGate_North = {
    Call(DisablePlayerInput, true)
    Set(LVar7, 0)
    Set(LVar8, 70)
    Set(LVar9, COLLIDER_monn)
    Set(LVarA, MODEL_monn)
    ExecWait(EVS_UseGate)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_UseGate_South = {
    Call(DisablePlayerInput, true)
    Set(LVar7, 0)
    Set(LVar8, -70)
    Set(LVar9, COLLIDER_mons)
    Set(LVarA, MODEL_mons)
    ExecWait(EVS_UseGate)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_UseGate_East = {
    Call(DisablePlayerInput, true)
    Set(LVar7, -70)
    Set(LVar8, 0)
    Set(LVar9, COLLIDER_mone)
    Set(LVarA, MODEL_mone)
    ExecWait(EVS_UseGate)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_UseGate_West = {
    Call(DisablePlayerInput, true)
    Set(LVar7, 70)
    Set(LVar8, 0)
    Set(LVar9, COLLIDER_monw)
    Set(LVarA, MODEL_monw)
    ExecWait(EVS_UseGate)
    Call(DisablePlayerInput, false)
    Return
    End
};
