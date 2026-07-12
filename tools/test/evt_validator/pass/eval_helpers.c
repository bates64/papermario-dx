#include "../evt_test.h"

static s32 TestEval0(void) {
    return 1;
}

static s32 TestEval1(s32 a) {
    return a + 1;
}

static s32 TestEval6(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    return a + b + c + d + e + f;
}

static f32 TestEvalF2(f32 a, f32 b) {
    return a + b;
}

static f32 TestEvalF6(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
    return a + b + c + d + e + f;
}

static void TestInvoke0(void) {
}

static void TestInvoke2(s32 a, s32 b) {
}

static void TestInvoke6(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
}

static void TestInvokeF1(f32 a) {
}

static void TestInvokeF6(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
}

static b32 TestIfEval1(s32 a) {
    return a > 0;
}

static b32 TestIfEval6(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    return (a + b + c + d + e + f) > 0;
}

static b32 TestIfEvalF1(f32 a) {
    return a > 0.0f;
}

static b32 TestIfEvalF6(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
    return (a + b + c + d + e + f) > 0.0f;
}

EvtScript EVS_EvalHelpers = {
    Eval(LVar0, TestEval0)
    Eval(LVar1, TestEval1, LVar0)
    Eval(LVar2, TestEval6, 1, 2, 3, 4, 5, 6)
    EvalF(LVar3, TestEvalF2, Float(1.0), Float(2.0))
    EvalF(LVar8, TestEvalF6, Float(1.0), Float(2.0), Float(3.0), Float(4.0), Float(5.0), Float(6.0))
    Invoke(TestInvoke0)
    Invoke(TestInvoke2, LVar0, LVar1)
    Invoke(TestInvoke6, 1, 2, 3, 4, 5, 6)
    InvokeF(TestInvokeF1, LVar3)
    InvokeF(TestInvokeF6, Float(1.0), Float(2.0), Float(3.0), Float(4.0), Float(5.0), Float(6.0))
    IfEval(TestIfEval1, LVar1)
        Set(LVar4, 1)
    Else
        Set(LVar4, 0)
    EndIf
    IfEval(TestIfEval6, 1, 2, 3, 4, 5, 6)
        Set(LVar9, 1)
    Else
        Set(LVar9, 0)
    EndIf
    IfNotEval(TestIfEval1, 0)
        Set(LVar5, 1)
    Else
        Set(LVar5, 0)
    EndIf
    IfEvalF(TestIfEvalF1, LVar3)
        Set(LVar6, 1)
    Else
        Set(LVar6, 0)
    EndIf
    IfEvalF(TestIfEvalF6, Float(1.0), Float(2.0), Float(3.0), Float(4.0), Float(5.0), Float(6.0))
        Set(LVarA, 1)
    Else
        Set(LVarA, 0)
    EndIf
    IfNotEvalF(TestIfEvalF1, Float(0.0))
        Set(LVar7, 1)
    Else
        Set(LVar7, 0)
    EndIf
    End
};
