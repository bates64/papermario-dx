#pragma once
#include "common.h"

#define EVT_TEST_TRACE_CAPACITY 32

BSS char EvtTestTrace[EVT_TEST_TRACE_CAPACITY];
BSS s32 EvtTestTraceLength;
BSS s32 EvtTestInvokeTotal;
BSS s32 EvtTestLerpIterations;
BSS s32 EvtTestRunnerID;

s32 EvtTestWords[] = { 11, 22, 33, 44 };
s32 EvtTestFloats[] = { Float(1.25), Float(2.5), Float(3.75) };
s32 EvtTestArray[4];

b32 evt_test_float_matches(f32 actual, f32 expected) {
    f32 difference = actual - expected;

    if (difference < 0.0f) {
        difference = -difference;
    }
    return difference < 0.001f;
}

API_CALLABLE(EvtTest_ResetTrace) {
    EvtTestTraceLength = 0;
    EvtTestTrace[0] = '\0';
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_Record) {
    Bytecode* args = script->ptrReadPos;
    s32 event = evt_get_variable(script, *args++);

    ASSERT(EvtTestTraceLength < EVT_TEST_TRACE_CAPACITY - 1);
    EvtTestTrace[EvtTestTraceLength++] = event;
    EvtTestTrace[EvtTestTraceLength] = '\0';
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_ExpectTrace) {
    const char* expected = (const char*)*script->ptrReadPos;

    ASSERT_MSG(
        strcmp(EvtTestTrace, expected) == 0,
        "EVT test expected trace %s but got %s",
        expected,
        EvtTestTrace
    );
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyArithmetic) {
    ASSERT(evt_get_variable(script, LVar0) == 12);
    ASSERT(evt_get_variable(script, LVar1) == 9);
    ASSERT(evt_get_variable(script, LVar2) == 7);
    ASSERT(evt_get_variable(script, LVar3) == 24);
    ASSERT(evt_get_variable(script, LVar4) == 8);
    ASSERT(evt_get_variable(script, LVar5) == 4);
    ASSERT(evt_get_variable(script, LVar6) == 5);
    ASSERT(evt_get_variable(script, LVar7) == 9);
    ASSERT(evt_get_variable(script, LVar8) == -1);
    ASSERT(evt_get_variable(script, LVar9) == 3);
    ASSERT(evt_get_variable(script, LVarA) == 8);
    ASSERT(evt_get_variable(script, LVarB) == 10);
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVarC), 2.0f));
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVarD), 3.5f));
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVarE), 3.0f));
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVarF), 3.0f));
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyControlFlow) {
    ASSERT(evt_get_variable(script, LVar1) == 8);
    ASSERT(evt_get_variable(script, LVar2) == 3);
    ASSERT(evt_get_variable(script, LVar3) == 4);
    ASSERT(evt_get_variable(script, LVar5) == 7);
    ASSERT(evt_get_variable(script, LVar6) == 9);
    ASSERT(evt_get_variable(script, LVar7) == 101);
    ASSERT(evt_get_variable(script, LVar8) == 5);
    ASSERT(evt_get_variable(script, LVar9) == 3);
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyLoopControlState) {
    Bytecode* args = script->ptrReadPos;
    s32 actual = evt_get_variable(script, *args++);
    s32 expected = evt_get_variable(script, *args++);

    ASSERT(script->loopDepth == -1);
    ASSERT(script->switchDepth == -1);
    ASSERT(!script->lerpActive);
    ASSERT(actual == expected);
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyStorage) {
    ASSERT(evt_get_variable(script, LVar0) == 11);
    ASSERT(evt_get_variable(script, LVar1) == 22);
    ASSERT(evt_get_variable(script, LVar2) == 33);
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVar3), 1.25f));
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVar4), 2.5f));
    ASSERT(EvtTestArray[0] == 15);
    ASSERT(EvtTestArray[2] == -4);
    return ApiStatus_DONE2;
}

s32 evt_test_eval(s32 a, s32 b, s32 c) {
    return a + b + c;
}

f32 evt_test_evalF(f32 a, f32 b) {
    return a * b;
}

void evt_test_invoke(s32 a, s32 b) {
    EvtTestInvokeTotal += a + b;
}

b32 evt_test_predicate(s32 value) {
    return value == 12;
}

API_CALLABLE(EvtTest_ResetEval) {
    EvtTestInvokeTotal = 0;
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyEval) {
    ASSERT(evt_get_variable(script, LVar0) == 12);
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, LVar1), 3.0f));
    ASSERT(evt_get_variable(script, LVar2) == 1);
    ASSERT(EvtTestInvokeTotal == 9);
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyArgs) {
    ASSERT(script->argCount == 5);
    ASSERT(evt_get_variable(script, ArgVar0) == 7);
    ASSERT(evt_get_variable(script, ArgVar1) == 12);
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, ArgVar2), 1.5f));
    ASSERT(evt_test_float_matches(evt_get_float_variable(script, ArgVar3), 2.5f));
    ASSERT(script->argVars[4] == LVarF);
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyArgCopyback) {
    ASSERT(evt_get_variable(script, LVar2) == 99);
    ASSERT(evt_get_variable(script, LFlag3));
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_ResetLerp) {
    EvtTestLerpIterations = 0;
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_CountLerpIteration) {
    EvtTestLerpIterations++;
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_VerifyLerp) {
    ASSERT(EvtTestLerpIterations == 3);
    ASSERT(evt_get_variable(script, LVar0) == 10);
    return ApiStatus_DONE2;
}

API_CALLABLE(EvtTest_Finish) {
    EvtTestRunnerID = 0;
    return ApiStatus_DONE2;
}

EvtScript EVS_EvtTestArithmetic = {
    Set(LVar0, 10)
    Add(LVar0, 2)
    Add(LVar1, 2, 3, 4)
    Sub(LVar2, LVar0, 5)
    Mul(LVar3, 2, 3, 4)
    Div(LVar4, LVar3, 3)
    Mod(LVar5, LVar3, 5)
    Neg(LVar6, -5)
    Abs(LVar7, -9)
    Sign(LVar8, -100)
    Min(LVar9, 7, 3, 5)
    Max(LVarA, 2, 8, 6)
    Clamp(LVarB, 15, 0, 10)
    SetF(LVarC, Float(1.5))
    AddF(LVarC, Float(0.5))
    SubF(LVarD, Float(5.0), Float(1.5))
    MulF(LVarE, Float(2.0), Float(1.5))
    DivF(LVarF, Float(7.5), Float(2.5))
    Call(EvtTest_VerifyArithmetic)
    End
};

EvtScript EVS_EvtTestControlFlow = {
    Set(LVar0, 5)
    Set(LVar1, 0)
    IfEq(LVar0, 5)
        Add(LVar1, 1)
    Else
        Add(LVar1, 100)
    EndIf
    IfNe(LVar0, 4)
        Add(LVar1, 1)
    EndIf
    IfLt(LVar0, 6)
        Add(LVar1, 1)
    EndIf
    IfGt(LVar0, 4)
        Add(LVar1, 1)
    EndIf
    IfLe(LVar0, 5)
        Add(LVar1, 1)
    EndIf
    IfGe(LVar0, 5)
        Add(LVar1, 1)
    EndIf
    IfRange(LVar0, 4, 6)
        Add(LVar1, 1)
    EndIf
    IfNotRange(LVar0, 6, 8)
        Add(LVar1, 1)
    EndIf
    Set(LVar2, 0)
    Set(LVar3, 0)
    Loop(5)
        Add(LVar2, 1)
        IfEq(LVar2, 2)
            ContinueLoop
        EndIf
        Add(LVar3, LVar2)
        IfEq(LVar2, 3)
            BreakLoop
        EndIf
    EndLoop
    Goto("TestTarget")
    Set(LVar3, 1000)
    Label("TestTarget")
    Set(LVar4, 3)
    Set(LVar5, 0)
    Switch(LVar4)
        CaseEq(2)
            Set(LVar5, 100)
            BreakSwitch
        CaseRange(3, 4)
            Set(LVar5, 7)
            BreakSwitch
        CaseDefault
            Set(LVar5, 200)
    EndSwitch
    Set(LVar6, 0)
    SwitchConst(1)
        CaseOrEq(0)
        CaseOrEq(1)
            Set(LVar6, 9)
        EndCaseGroup
        CaseDefault
            Set(LVar6, 100)
    EndSwitch
    Set(LVar7, 0)
    IfFlag(10, 2)
        Set(LVar7, 1)
    EndIf
    IfNotFlag(8, 2)
        Add(LVar7, 100)
    EndIf
    Set(LVar8, 0)
    Set(LVar9, 0)
    Loop(3)
        Add(LVar8, 1)
        IfLt(LVar8, 3)
            RetryLoop
        EndIf
        Add(LVar9, 1)
    EndLoop
    Call(EvtTest_VerifyControlFlow)
    End
};

EvtScript EVS_EvtTestLoopControl = {
    Set(LVar0, 0)
    Loop(1)
        Switch(LVar0)
            CaseDefault
                SwitchConst(0)
                    CaseDefault
                        BreakLoop
                        Switch(LVar0)
                            CaseDefault
                                SwitchConst(0)
                                    CaseDefault
                                        Add(LVar0, 100)
                                EndSwitch
                        EndSwitch
                EndSwitch
        EndSwitch
    EndLoop
    Call(EvtTest_VerifyLoopControlState, LVar0, 0)

    Set(LVar0, 0)
    Loop(2)
        Switch(LVar0)
            CaseDefault
                SwitchConst(0)
                    CaseDefault
                        Add(LVar0, 1)
                        ContinueLoop
                EndSwitch
        EndSwitch
    EndLoop
    Call(EvtTest_VerifyLoopControlState, LVar0, 2)

    Set(LVar0, 0)
    Loop(1)
        Switch(LVar0)
            CaseDefault
                SwitchConst(0)
                    CaseDefault
                        Add(LVar0, 1)
                        IfLt(LVar0, 3)
                            RetryLoop
                        EndIf
                EndSwitch
        EndSwitch
    EndLoop
    Call(EvtTest_VerifyLoopControlState, LVar0, 3)

    Lerp(LVar0, 0, 10, 2, EASING_LINEAR)
        SwitchConst(0)
            CaseDefault
                BreakLoop
        EndSwitch
    EndLerp
    Call(EvtTest_VerifyLoopControlState, 0, 0)

    Set(LVar0, 0)
    SwitchConst(0)
        CaseDefault
            Loop(2)
                Loop(2)
                    Add(LVar0, 1)
                    BreakSwitch
                EndLoop
            EndLoop
    EndSwitch
    Call(EvtTest_VerifyLoopControlState, LVar0, 1)

    Set(LVar0, 0)
    Loop(2)
        SwitchConst(0)
            CaseEq(0)
                BreakSwitch
            CaseDefault
                SwitchConst(0)
                    CaseDefault
                        Loop(2)
                            Add(LVar0, 100)
                        EndLoop
                EndSwitch
        EndSwitch
        Add(LVar0, 1)
    EndLoop
    Call(EvtTest_VerifyLoopControlState, LVar0, 2)

    Set(LVar0, 0)
    SwitchConst(0)
        CaseDefault
            Lerp(LVar0, 0, 10, 2, EASING_LINEAR)
                BreakSwitch
            EndLerp
    EndSwitch
    Call(EvtTest_VerifyLoopControlState, 0, 0)
    End
};

EvtScript EVS_EvtTestStorage = {
    UseBuf(Ref(EvtTestWords))
    BufRead(LVar0, LVar1)
    BufPeek(LVar2, 0)
    UseFBuf(Ref(EvtTestFloats))
    FBufRead(LVar3, LVar4)
    UseArray(Ref(EvtTestArray))
    Set(ArrayVar(0), 10)
    Add(ArrayVar(0), 5)
    Set(ArrayVar(2), -4)
    Call(EvtTest_VerifyStorage)
    End
};

EvtScript EVS_EvtTestEval = {
    Eval(LVar0, evt_test_eval, 3, 4, 5)
    EvalF(LVar1, evt_test_evalF, Float(1.5), Float(2.0))
    Invoke(evt_test_invoke, 4, 5)
    Set(LVar2, 0)
    IfEval(evt_test_predicate, LVar0)
        Set(LVar2, 1)
    EndIf
    Call(EvtTest_VerifyEval)
    End
};

EvtScript EVS_EvtTestArgsChild = {
    ExpectArgs(5)
    Call(EvtTest_VerifyArgs)
    Set(LVar2, 99)
    Set(LFlag3, true)
    End
};

EvtScript EVS_EvtTestArgsParent = {
    Set(LVar0, 12)
    SetF(LVar1, Float(2.5))
    Set(LVarF, 123)
    ExecWait(EVS_EvtTestArgsChild, 7, ARG_INT(LVar0), Float(1.5), ARG_FLOAT(LVar1), LVarF)
    Call(EvtTest_VerifyArgCopyback)
    End
};

EvtScript EVS_EvtTestLerp = {
    Lerp(LVar0, 0, 10, 2, EASING_LINEAR)
        Call(EvtTest_CountLerpIteration)
    EndLerp
    End
};

EvtScript EVS_EvtTestNaturalFinally = {
    ChildThread
        Finally
            Call(EvtTest_Record, 'C')
        EndChildThread
    Return
    Finally
        Call(EvtTest_Record, 'P')
    End
};

EvtScript EVS_EvtTestForcedFinally = {
    ChildThread
        Wait(100)
        Finally
            Call(EvtTest_Record, 'C')
        EndChildThread
    Wait(100)
    Finally
        Call(EvtTest_Record, 'P')
    End
};

EvtScript EVS_EvtTestCompanion = {
    Wait(100)
    Finally
        Call(EvtTest_Record, 'C')
    End
};

EvtScript EVS_EvtTestCompanionOwner = {
    ExecGetID(LVar0, EVS_EvtTestCompanion)
    Wait(100)
    Finally
        KillScript(LVar0)
        Call(EvtTest_Record, 'P')
    End
};

EvtScript EVS_EvtTestDetached = {
    Wait(3)
    Call(EvtTest_Record, 'D')
    End
};

EvtScript EVS_EvtTestDetachedOwner = {
    ExecGetID(LVarF, EVS_EvtTestDetached)
    Return
    Finally
        Call(EvtTest_Record, 'P')
    End
};

EvtScript EVS_EvtTestAwaitChildren = {
    ChildThread
        Wait(2)
        Call(EvtTest_Record, 'C')
    EndChildThread
    AwaitChildren
    Call(EvtTest_Record, 'P')
    End
};

EvtScript EVS_EvtPlusInstrumentation = {
    DebugPrint("[EVT TEST] starting")

    ExecWait(EVS_EvtTestArithmetic)
    DebugPrint("[EVT TEST] arithmetic PASS")

    ExecWait(EVS_EvtTestControlFlow)
    DebugPrint("[EVT TEST] control flow PASS")

    ExecWait(EVS_EvtTestLoopControl)
    DebugPrint("[EVT TEST] loop cleanup PASS")

    ExecWait(EVS_EvtTestStorage)
    DebugPrint("[EVT TEST] buffers PASS")

    Call(EvtTest_ResetEval)
    ExecWait(EVS_EvtTestEval)
    DebugPrint("[EVT TEST] eval PASS")

    ExecWait(EVS_EvtTestArgsParent)
    DebugPrint("[EVT TEST] arguments PASS")

    Call(EvtTest_ResetLerp)
    ExecWait(EVS_EvtTestLerp)
    Call(EvtTest_VerifyLerp)
    DebugPrint("[EVT TEST] lerp PASS")

    Call(EvtTest_ResetTrace)
    ExecWait(EVS_EvtTestNaturalFinally)
    Call(EvtTest_ExpectTrace, Ref("CP"))
    DebugPrint("[EVT TEST] natural Finally PASS")

    Call(EvtTest_ResetTrace)
    ExecGetID(LVarF, EVS_EvtTestForcedFinally)
    // give the detached parent one update to start its child
    Wait(2)
    KillScript(LVarF)
    Call(EvtTest_ExpectTrace, Ref("CP"))
    DebugPrint("[EVT TEST] forced Finally PASS")

    Call(EvtTest_ResetTrace)
    ExecGetID(LVarF, EVS_EvtTestCompanionOwner)
    // give the detached owner one update to start its companion
    Wait(2)
    KillScript(LVarF)
    Call(EvtTest_ExpectTrace, Ref("CP"))
    DebugPrint("[EVT TEST] companion cleanup PASS")

    Call(EvtTest_ResetTrace)
    ExecWait(EVS_EvtTestDetachedOwner)
    Call(EvtTest_ExpectTrace, Ref("P"))
    AwaitScript(LVarF)
    Call(EvtTest_ExpectTrace, Ref("PD"))
    DebugPrint("[EVT TEST] detached script PASS")

    Call(EvtTest_ResetTrace)
    ExecWait(EVS_EvtTestAwaitChildren)
    Call(EvtTest_ExpectTrace, Ref("CP"))
    DebugPrint("[EVT TEST] AwaitChildren PASS")

    Call(EvtTest_Finish)
    DebugPrint("[EVT TEST] ALL VM TESTS PASS")
    End
};
