#include "../evt_test.h"

EvtScript EVS_ArithmeticArgs = {
    Add(LVar0, 1, 2, 3, 4)
    Sub(LVar1, LVar0, 3)
    Mul(LVar2, 2, 3, 4)
    Div(LVar3, LVar2, 2)
    Mod(LVar4, LVar2, 5)
    AddF(LVar5, Float(1.0), Float(2.0), Float(3.0))
    SubF(LVar6, LVar5, Float(1.0))
    MulF(LVar7, Float(2.0), Float(3.0), Float(4.0))
    DivF(LVar8, LVar7, Float(2.0))
    End
};
