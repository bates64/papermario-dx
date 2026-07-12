#include "common.h"

#include <stdio.h>
#include <stdlib.h>

extern s32 gNumScripts;
extern ScriptList* gCurrentScriptListPtr;
extern s32* gMapVars;
extern u32* gMapFlags;
extern s32 gScriptListCount;
extern s32 IsUpdatingScripts;

s32 evt_execute_next_command(Evt* script);

GameStatus gTestGameStatus;
GameStatus* gGameStatusPtr = &gTestGameStatus;
s32 gTimeFreezeMode = TIME_FREEZE_NONE;
static void* gExpectedHeapFree;
static b32 gExpectedHeapFreeSeen;
static s32 gTestGlobalFlags[2048];
static s32 gTestAreaFlags[256];
static s8 gTestGlobalBytes[512];
static s8 gTestAreaBytes[16];

void* heap_malloc(s32 size) {
    return calloc(1, size);
}

s32 heap_free(void* ptr) {
    if (ptr == gExpectedHeapFree) {
        gExpectedHeapFreeSeen = true;
    }
    free(ptr);
    return 0;
}

void dx_debug_evt_force_detach(Evt* evt) {
}

void dx_debug_evt_reset(void) {
}

void clear_virtual_entity_list(void) {
}

void reset_model_animators(void) {
}

void is_debug_panic(const char* message) {
    fprintf(stderr, "EVT panic: %s\n", message);
    abort();
}

void backtrace_address_to_string(u32 address, char* dest, s32 line) {
    sprintf(dest, "0x%08lX", address);
}

f32 update_lerp(s32 easing, f32 start, f32 end, s32 elapsed, s32 duration) {
    return end;
}

Trigger* create_trigger(TriggerBlueprint* bp) {
    return calloc(1, sizeof(Trigger));
}

void delete_trigger(Trigger* trigger) {
    free(trigger);
}

s32 is_another_trigger_bound(Trigger* trigger, EvtScript* script) {
    return false;
}

s32 get_global_flag(s32 index) {
    return gTestGlobalFlags[index];
}

s32 set_global_flag(s32 index) {
    return gTestGlobalFlags[index] = true;
}

s32 clear_global_flag(s32 index) {
    return gTestGlobalFlags[index] = false;
}

s32 get_area_flag(s32 index) {
    return gTestAreaFlags[index];
}

s32 set_area_flag(s32 index) {
    return gTestAreaFlags[index] = true;
}

s32 clear_area_flag(s32 index) {
    return gTestAreaFlags[index] = false;
}

s32 get_global_byte(s32 index) {
    return gTestGlobalBytes[index];
}

s8 set_global_byte(s32 index, s32 value) {
    return gTestGlobalBytes[index] = value;
}

s32 get_area_byte(s32 index) {
    return gTestAreaBytes[index];
}

s8 set_area_byte(s32 index, s32 value) {
    return gTestAreaBytes[index] = value;
}

static char gTrace[64];
static s32 gTraceLen;
static s32 gFailures;
static Evt* gSiblingToKill;
static s32 gCapturedScriptID;
static s32 gInvokeTotal;
static s32 gLerpIterations;

static s32 gTestWords[] = { 11, 22, 33, 44 };
static s32 gTestFloats[] = { Float(1.25), Float(2.5), Float(3.75) };
static s32 gTestArray[4];
static s32 gTestFlagArray[2];

extern EvtScript EVS_Companion;

#define CHECK(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            gFailures++; \
        } \
    } while (0)

static b32 has_owned_child(Evt* script) {
    s32 i;

    if (script->blockingChild != nullptr) {
        return true;
    }
    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate != nullptr && candidate->threadParent == script) {
            return true;
        }
    }
    return false;
}

static API_CALLABLE(Record) {
    char marker = evt_get_variable(script, *script->ptrReadPos);

    CHECK(EvtCurrentScript == script);
    if (marker == 'P') {
        CHECK(!has_owned_child(script));
    }
    CHECK(gTraceLen < ARRAY_COUNT(gTrace) - 1);
    gTrace[gTraceLen++] = marker;
    gTrace[gTraceLen] = '\0';
    return ApiStatus_DONE2;
}

static API_CALLABLE(CheckCopyback) {
    CHECK(script->varTable[1] == 42);
    return Record(script, isInitialCall);
}

static API_CALLABLE(KillSibling) {
    kill_script(gSiblingToKill);
    return ApiStatus_DONE2;
}

static API_CALLABLE(Fail) {
    return -1;
}

static API_CALLABLE(StartCompanion) {
    start_script(&EVS_Companion, EVT_PRIORITY_0, 0);
    return ApiStatus_DONE2;
}

static API_CALLABLE(StartOwnedChild) {
    start_child_script(script, &EVS_Companion, 0);
    return ApiStatus_DONE2;
}

static API_CALLABLE(KillSelfAndStartCompanion) {
    kill_script(script);
    CHECK(!does_script_exist_by_ref(script));
    start_script(&EVS_Companion, EVT_PRIORITY_0, 0);
    return ApiStatus_FINISH;
}

static API_CALLABLE(KillAllFromCall) {
    kill_all_scripts();
    return ApiStatus_DONE2;
}

static API_CALLABLE(CaptureScriptID) {
    gCapturedScriptID = script->varTable[0];
    return ApiStatus_DONE2;
}

static void check_float(f32 actual, f32 expected) {
    f32 difference = actual - expected;

    if (difference < 0.0f) {
        difference = -difference;
    }
    CHECK(difference < 0.001f);
}

static API_CALLABLE(VerifyArithmetic) {
    CHECK(evt_get_variable(script, LVar0) == 12);
    CHECK(evt_get_variable(script, LVar1) == 9);
    CHECK(evt_get_variable(script, LVar2) == 7);
    CHECK(evt_get_variable(script, LVar3) == 24);
    CHECK(evt_get_variable(script, LVar4) == 8);
    CHECK(evt_get_variable(script, LVar5) == 4);
    CHECK(evt_get_variable(script, LVar6) == 5);
    CHECK(evt_get_variable(script, LVar7) == 9);
    CHECK(evt_get_variable(script, LVar8) == -1);
    CHECK(evt_get_variable(script, LVar9) == 3);
    CHECK(evt_get_variable(script, LVarA) == 8);
    CHECK(evt_get_variable(script, LVarB) == 10);
    check_float(evt_get_float_variable(script, LVarC), 2.0f);
    check_float(evt_get_float_variable(script, LVarD), 3.5f);
    check_float(evt_get_float_variable(script, LVarE), 3.0f);
    check_float(evt_get_float_variable(script, LVarF), 3.0f);
    return ApiStatus_DONE2;
}

static API_CALLABLE(VerifyControlFlow) {
    CHECK(evt_get_variable(script, LVar1) == 8);
    CHECK(evt_get_variable(script, LVar2) == 3);
    CHECK(evt_get_variable(script, LVar3) == 4);
    CHECK(evt_get_variable(script, LVar5) == 7);
    CHECK(evt_get_variable(script, LVar6) == 9);
    CHECK(evt_get_variable(script, LVar7) == 101);
    return ApiStatus_DONE2;
}

static API_CALLABLE(VerifyStorage) {
    CHECK(evt_get_variable(script, LVar0) == 11);
    CHECK(evt_get_variable(script, LVar1) == 22);
    check_float(evt_get_float_variable(script, LVar2), 1.25f);
    check_float(evt_get_float_variable(script, LVar3), 2.5f);
    CHECK(evt_get_variable(script, LVar4) == 44);
    CHECK(evt_get_variable(script, MapVar(3)) == 1234);
    CHECK(evt_get_variable(script, LFlag4));
    CHECK(evt_get_variable(script, MapFlag(35)));
    CHECK(evt_get_variable(script, AreaFlag(7)));
    CHECK(evt_get_variable(script, GameFlag(17)));
    CHECK(evt_get_variable(script, AreaByte(2)) == 23);
    CHECK(evt_get_variable(script, GameByte(9)) == 91);
    CHECK(gTestArray[0] == 15);
    CHECK(gTestArray[2] == -4);
    CHECK(evt_get_variable(script, ArrayFlag(37)));
    return ApiStatus_DONE2;
}

static s32 TestEval(s32 a, s32 b, s32 c) {
    return a + b + c;
}

static f32 TestEvalF(f32 a, f32 b) {
    return a * b;
}

static void TestInvoke(s32 a, s32 b) {
    gInvokeTotal += a + b;
}

static b32 TestPredicate(s32 value) {
    return value == 12;
}

static API_CALLABLE(VerifyEval) {
    CHECK(evt_get_variable(script, LVar0) == 12);
    check_float(evt_get_float_variable(script, LVar1), 3.0f);
    CHECK(evt_get_variable(script, LVar2) == 1);
    CHECK(gInvokeTotal == 9);
    return ApiStatus_DONE2;
}

static API_CALLABLE(VerifyArgs) {
    CHECK(evt_get_variable(script, ArgVar0) == 7);
    CHECK(evt_get_variable(script, ArgVar1) == 12);
    check_float(evt_get_float_variable(script, ArgVar2), 1.5f);
    check_float(evt_get_float_variable(script, ArgVar3), 2.5f);
    return ApiStatus_DONE2;
}

static API_CALLABLE(VerifyArgCopyback) {
    CHECK(evt_get_variable(script, LVar2) == 99);
    CHECK(evt_get_variable(script, LFlag3));
    return ApiStatus_DONE2;
}

static API_CALLABLE(CountLerpIteration) {
    gLerpIterations++;
    return ApiStatus_DONE2;
}

static API_CALLABLE(BlockForever) {
    if (isInitialCall) {
        Record(script, isInitialCall);
    }
    return ApiStatus_BLOCK;
}

static API_CALLABLE(VerifyJump) {
    CHECK(evt_get_variable(script, LVar0) == 2);
    return ApiStatus_DONE2;
}

EvtScript EVS_NaturalNeither = {
    ChildThread
    EndChildThread
    End
};

EvtScript EVS_NaturalParent = {
    ChildThread
    EndChildThread
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_NaturalChild = {
    ChildThread
        Finally
            Call(Record, 'C')
        EndChildThread
    End
};

EvtScript EVS_NaturalBoth = {
    ChildThread
        Finally
            Call(Record, 'C')
        EndChildThread
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_EarlyReturnBoth = {
    ChildThread
        Finally
            Call(Record, 'C')
        EndChildThread
    Return
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_ForcedNeither = {
    ChildThread
        Wait(100)
    EndChildThread
    Wait(100)
    End
};

EvtScript EVS_ForcedParent = {
    ChildThread
        Wait(100)
    EndChildThread
    Wait(100)
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_ForcedChild = {
    ChildThread
        Wait(100)
        Finally
            Call(Record, 'C')
        EndChildThread
    Wait(100)
    End
};

EvtScript EVS_ForcedBoth = {
    ChildThread
        Wait(100)
        Finally
            Call(Record, 'C')
        EndChildThread
    Wait(100)
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_CopybackChild = {
    Finally
        Set(LVar1, 42)
        Call(Record, 'C')
    End
};

EvtScript EVS_CopybackParent = {
    ExecWait(EVS_CopybackChild)
    Finally
        Call(CheckCopyback, 'P')
    End
};

EvtScript EVS_Companion = {
    Wait(100)
    Finally
        Call(Record, 'C')
    End
};

EvtScript EVS_CompanionOwner = {
    ExecGetID(EVS_Companion, LVar0)
    Wait(100)
    Finally
        KillScript(LVar0)
        Call(Record, 'P')
    End
};

EvtScript EVS_SelfKill = {
    Finally
        Call(Record, 'A')
        KillScript(LVar0)
        Call(Record, 'B')
    End
};

EvtScript EVS_CycleA = {
    Wait(100)
    Finally
        Call(Record, 'A')
        KillScript(LVar0)
        Call(Record, 'a')
    End
};

EvtScript EVS_CycleB = {
    Wait(100)
    Finally
        Call(Record, 'B')
        KillScript(LVar0)
        Call(Record, 'b')
    End
};

EvtScript EVS_ChildKillsParent = {
    ChildThread
        Finally
            Call(Record, 'C')
            KillScript(LVar0)
            Call(Record, 'c')
        EndChildThread
    Wait(100)
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_ChildKillsParentNoFinally = {
    ChildThread
        Finally
            Call(Record, 'C')
            KillScript(LVar0)
            Call(Record, 'c')
        EndChildThread
    Wait(100)
    End
};

EvtScript EVS_BlockingChildKillsParent = {
    Finally
        Set(LVar1, 42)
        Call(Record, 'C')
        KillScript(LVar0)
        Call(Record, 'c')
    End
};

EvtScript EVS_BlockingParentKilledByChild = {
    ExecWait(EVS_BlockingChildKillsParent)
    Finally
        Call(CheckCopyback, 'P')
    End
};

EvtScript EVS_ActiveCaller = {
    KillScript(LVar0)
    Finally
        Call(Record, 'A')
    End
};

EvtScript EVS_ActiveTarget = {
    Wait(100)
    Finally
        Call(Record, 'B')
        KillScript(LVar0)
        Call(Record, 'b')
    End
};

EvtScript EVS_SiblingCleanup = {
    ChildThread
        Wait(100)
        Finally
            Call(Record, 'A')
            Call(KillSibling)
            Call(Record, 'a')
        EndChildThread
    ChildThread
        Wait(100)
        Finally
            Call(Record, 'B')
            Call(Record, 'b')
        EndChildThread
    Wait(100)
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_ErrorFinally = {
    Finally
        Call(Fail)
    End
};

EvtScript EVS_ExecFinally = {
    Finally
        Exec(EVS_Companion)
        ExecGetID(EVS_Companion, LVar0)
        Call(CaptureScriptID)
        Call(Record, 'P')
    End
};

EvtScript EVS_CallStartsScriptFinally = {
    Finally
        Call(StartCompanion)
        Call(Record, 'P')
    End
};

EvtScript EVS_ExecWaitFinally = {
    Finally
        ExecWait(EVS_Companion)
    End
};

EvtScript EVS_CallStartsOwnedFinally = {
    Finally
        Call(StartOwnedChild)
    End
};

EvtScript EVS_SelfReplaceBeforeFinally = {
    Call(KillSelfAndStartCompanion)
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_KillAllFiller = {
    Wait(100)
    End
};

EvtScript EVS_KillAllSpawner = {
    Wait(100)
    Finally
        Exec(EVS_Companion)
        Call(Record, 'S')
    End
};

EvtScript EVS_KillAllFromActiveCommand = {
    Call(KillAllFromCall)
    Finally
        Call(Record, 'A')
    End
};

EvtScript EVS_TestArithmetic = {
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
    Call(VerifyArithmetic)
    End
};

EvtScript EVS_TestControlFlow = {
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
    Call(VerifyControlFlow)
    End
};

EvtScript EVS_TestStorage = {
    UseBuf(gTestWords)
    BufRead(LVar0, LVar1)
    BufPeek(LVar4, 1)
    UseFBuf(gTestFloats)
    FBufRead(LVar2, LVar3)
    Set(MapVar(3), 1234)
    Set(LFlag4, true)
    Set(MapFlag(35), true)
    Set(AreaFlag(7), true)
    Set(GameFlag(17), true)
    Set(AreaByte(2), 23)
    Set(GameByte(9), 91)
    UseArray(gTestArray)
    Set(ArrayVar(0), 10)
    Add(ArrayVar(0), 5)
    Set(ArrayVar(2), -4)
    UseFlagArray(gTestFlagArray)
    Set(ArrayFlag(37), true)
    Call(VerifyStorage)
    End
};

EvtScript EVS_TestEval = {
    Eval(LVar0, TestEval, 3, 4, 5)
    EvalF(LVar1, TestEvalF, Float(1.5), Float(2.0))
    Invoke(TestInvoke, 4, 5)
    Set(LVar2, 0)
    IfEval(TestPredicate, LVar0)
        Set(LVar2, 1)
    EndIf
    Call(VerifyEval)
    End
};

EvtScript EVS_TestArgsChild = {
    ExpectArgs(4)
    Call(VerifyArgs)
    Set(LVar2, 99)
    Set(LFlag3, true)
    End
};

EvtScript EVS_TestArgsParent = {
    Set(LVar0, 12)
    SetF(LVar1, Float(2.5))
    ExecWait(EVS_TestArgsChild, 7, ARG_INT(LVar0), Float(1.5), ARG_FLOAT(LVar1))
    Call(VerifyArgCopyback)
    End
};

EvtScript EVS_TestScheduler = {
    Thread
        Call(Record, 'T')
    EndThread
    ChildThread
        Call(Record, 'C')
    EndChildThread
    Call(Record, 'p')
    Wait(2)
    Call(Record, 'Q')
    End
};

EvtScript EVS_TestLerp = {
    Lerp(LVar0, 0, 10, 2, EASING_LINEAR)
        Call(CountLerpIteration)
    EndLerp
    End
};

EvtScript EVS_TestLongLerp = {
    Lerp(LVar0, 0, 10, 100, EASING_LINEAR)
        Call(CountLerpIteration)
    EndLerp
    Finally
        Call(Record, 'L')
    End
};

EvtScript EVS_TestBlockedCall = {
    Call(BlockForever, 'B')
    Finally
        Call(Record, 'F')
    End
};

EvtScript EVS_TestJumpTarget = {
    Add(LVar0, 1)
    Call(VerifyJump)
    Finally
        Call(Record, 'J')
    End
};

EvtScript EVS_TestJump = {
    Set(LVar0, 1)
    Jump(EVS_TestJumpTarget)
    Set(LVar0, 100)
    End
};

EvtScript EVS_TestArgsWait = {
    ExpectArgs(2)
    Wait(100)
    Finally
        Call(Record, 'A')
    End
};

EvtScript EVS_TestArgsKill = {
    ExecGetID(EVS_TestArgsWait, LVar0, 7, 8)
    Wait(100)
    Finally
        KillScript(LVar0)
        Call(Record, 'P')
    End
};

static ScriptList gTestScriptList;
static s32 gTestMapVars[MAX_MAPVARS];
static u32 gTestMapFlags[MAX_MAPFLAGS];

static void reset_test(void) {
    CHECK(gNumScripts == 0);
    memset(&gTestScriptList, 0, sizeof(gTestScriptList));
    memset(&gTestGameStatus, 0, sizeof(gTestGameStatus));
    memset(gTestMapVars, 0, sizeof(gTestMapVars));
    memset(gTestMapFlags, 0, sizeof(gTestMapFlags));
    gCurrentScriptListPtr = &gTestScriptList;
    gMapVars = gTestMapVars;
    gMapFlags = gTestMapFlags;
    gNumScripts = 0;
    gScriptListCount = 0;
    IsUpdatingScripts = false;
    EvtCurrentScript = nullptr;
    gSiblingToKill = nullptr;
    gCapturedScriptID = -1;
    gInvokeTotal = 0;
    gLerpIterations = 0;
    gExpectedHeapFree = nullptr;
    gExpectedHeapFreeSeen = false;
    memset(gTestGlobalFlags, 0, sizeof(gTestGlobalFlags));
    memset(gTestAreaFlags, 0, sizeof(gTestAreaFlags));
    memset(gTestGlobalBytes, 0, sizeof(gTestGlobalBytes));
    memset(gTestAreaBytes, 0, sizeof(gTestAreaBytes));
    memset(gTestArray, 0, sizeof(gTestArray));
    memset(gTestFlagArray, 0, sizeof(gTestFlagArray));
    gTraceLen = 0;
    gTrace[0] = '\0';
}

static void expect_trace(const char* expected) {
    if (strcmp(gTrace, expected) != 0) {
        fprintf(stderr, "FAIL trace: expected '%s', got '%s'\n", expected, gTrace);
        gFailures++;
    }
}

static Evt* start_test_script(EvtScript* source) {
    return start_script(source, EVT_PRIORITY_0, 0);
}

static Evt* find_child_thread(Evt* parent) {
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate != nullptr && candidate->threadParent == parent) {
            return candidate;
        }
    }
    return nullptr;
}

static Evt* find_script_by_id(s32 id) {
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* script = (*gCurrentScriptListPtr)[i];

        if (script != nullptr && script->id == id) {
            return script;
        }
    }
    return nullptr;
}

static void check_all_scripts_detached(s32 expectedCount) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* script = (*gCurrentScriptListPtr)[i];

        if (script != nullptr) {
            CHECK(script->blockingParent == nullptr);
            CHECK(script->threadParent == nullptr);
            count++;
        }
    }
    CHECK(count == expectedCount);
}

static void test_natural_matrix(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_NaturalNeither);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 0);
    expect_trace("");

    reset_test();
    script = start_test_script(&EVS_NaturalParent);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 0);
    expect_trace("P");

    reset_test();
    script = start_test_script(&EVS_NaturalChild);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 0);
    expect_trace("C");

    reset_test();
    script = start_test_script(&EVS_NaturalBoth);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 0);
    expect_trace("CP");

    reset_test();
    script = start_test_script(&EVS_EarlyReturnBoth);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 0);
    expect_trace("CP");
}

static void test_forced_matrix(void) {
    EvtScript* scripts[] = { &EVS_ForcedNeither, &EVS_ForcedParent, &EVS_ForcedChild, &EVS_ForcedBoth };
    const char* traces[] = { "", "P", "C", "CP" };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(scripts); i++) {
        Evt* parent;

        reset_test();
        parent = start_test_script(scripts[i]);
        evt_execute_next_command(parent);
        CHECK(gNumScripts == 2);
        kill_script(parent);
        CHECK(gNumScripts == 0);
        expect_trace(traces[i]);
    }
}

static void test_exec_wait_copyback(void) {
    Evt* parent;

    reset_test();
    parent = start_test_script(&EVS_CopybackParent);
    evt_execute_next_command(parent);
    CHECK(parent->blockingChild != nullptr);
    kill_script(parent);
    CHECK(gNumScripts == 0);
    expect_trace("CP");
}

static void test_detached_companion(void) {
    Evt* parent;

    reset_test();
    parent = start_test_script(&EVS_CompanionOwner);
    evt_execute_next_command(parent);
    CHECK(gNumScripts == 2);
    kill_script(parent);
    CHECK(gNumScripts == 0);
    expect_trace("CP");
}

static void test_self_kill(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_SelfKill);
    script->varTable[0] = script->id;
    kill_script(script);
    CHECK(gNumScripts == 0);
    expect_trace("AB");
}

static void test_cycle(void) {
    Evt* scriptA;
    Evt* scriptB;

    reset_test();
    scriptA = start_test_script(&EVS_CycleA);
    scriptB = start_test_script(&EVS_CycleB);
    scriptA->varTable[0] = scriptB->id;
    scriptB->varTable[0] = scriptA->id;
    kill_script(scriptA);
    CHECK(gNumScripts == 0);
    expect_trace("ABba");
}

static void test_child_kills_parent(EvtScript* source, const char* expected) {
    Evt* parent;
    Evt* child;

    reset_test();
    parent = start_test_script(source);
    parent->varTable[0] = parent->id;
    evt_execute_next_command(parent);
    child = find_child_thread(parent);
    CHECK(child != nullptr);
    evt_execute_next_command(child);
    CHECK(gNumScripts == 0);
    expect_trace(expected);
}

static void test_blocking_child_kills_parent(void) {
    Evt* parent;
    Evt* child;

    reset_test();
    parent = start_test_script(&EVS_BlockingParentKilledByChild);
    parent->varTable[0] = parent->id;
    evt_execute_next_command(parent);
    child = parent->blockingChild;
    CHECK(child != nullptr);
    evt_execute_next_command(child);
    CHECK(gNumScripts == 0);
    expect_trace("CcP");
}

static void test_active_caller_is_killed(void) {
    Evt* caller;
    Evt* target;

    reset_test();
    caller = start_test_script(&EVS_ActiveCaller);
    target = start_test_script(&EVS_ActiveTarget);
    caller->varTable[0] = target->id;
    target->varTable[0] = caller->id;
    evt_execute_next_command(caller);
    CHECK(gNumScripts == 0);
    expect_trace("BbA");
}

static void test_sibling_cleanup_mutates_child_list(void) {
    Evt* parent;
    Evt* firstChild = nullptr;
    Evt* secondChild = nullptr;
    s32 i;

    reset_test();
    parent = start_test_script(&EVS_SiblingCleanup);
    evt_execute_next_command(parent);
    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate != nullptr && candidate->threadParent == parent) {
            if (firstChild == nullptr) {
                firstChild = candidate;
            } else {
                secondChild = candidate;
            }
        }
    }
    CHECK(firstChild != nullptr);
    CHECK(secondChild != nullptr);
    gSiblingToKill = secondChild;
    kill_script(parent);
    CHECK(gNumScripts == 0);
    expect_trace("ABbaP");
}

static void test_normal_command_can_replace_terminating_self(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_SelfReplaceBeforeFinally);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 1);
    expect_trace("P");
    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("PC");
}

static void test_finalizer_can_start_detached_scripts(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_ExecFinally);
    kill_script(script);
    CHECK(gNumScripts == 2);
    CHECK(does_script_exist(gCapturedScriptID));
    check_all_scripts_detached(2);
    expect_trace("P");
    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("PCC");

    reset_test();
    script = start_test_script(&EVS_CallStartsScriptFinally);
    kill_script(script);
    CHECK(gNumScripts == 1);
    check_all_scripts_detached(1);
    expect_trace("P");
    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("PC");
}

static void test_kill_all_rescans_for_spawned_scripts(void) {
    reset_test();
    start_test_script(&EVS_KillAllFiller);
    start_test_script(&EVS_KillAllSpawner);
    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("SC");
}

static void test_kill_all_from_active_command(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_KillAllFromActiveCommand);
    evt_execute_next_command(script);
    CHECK(gNumScripts == 0);
    expect_trace("A");
}

static void test_clear_script_list_bypasses_finalizers(void) {
    Evt* parent;

    reset_test();
    gTestGameStatus.context = CONTEXT_WORLD;
    clear_script_list();
    parent = start_test_script(&EVS_ForcedBoth);
    evt_execute_next_command(parent);
    CHECK(gNumScripts == 2);
    clear_script_list();
    CHECK(gNumScripts == 0);
    CHECK(EvtCurrentScript == nullptr);
    expect_trace("");
}

static void test_kill_blocked_call(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_TestBlockedCall);
    evt_execute_next_command(script);
    CHECK(script->blocked);
    expect_trace("B");
    kill_script(script);
    CHECK(gNumScripts == 0);
    expect_trace("BF");
}

static void test_kill_suspended_tree(void) {
    Evt* parent;
    Evt* child;

    reset_test();
    parent = start_test_script(&EVS_ForcedBoth);
    evt_execute_next_command(parent);
    child = find_child_thread(parent);
    CHECK(child != nullptr);
    suspend_all_script(parent->id);
    CHECK(parent->stateFlags & EVT_FLAG_PAUSED);
    CHECK(child->stateFlags & EVT_FLAG_PAUSED);
    kill_script(parent);
    CHECK(gNumScripts == 0);
    expect_trace("CP");
}

static void test_jump_restarts_script(void) {
    reset_test();
    evt_execute_next_command(start_test_script(&EVS_TestJump));
    CHECK(gNumScripts == 0);
    expect_trace("J");
}

static void test_restart_clears_lerp_state(void) {
    Evt* script;

    reset_test();
    script = start_test_script(&EVS_TestLongLerp);
    evt_execute_next_command(script);
    CHECK(script->lerpActive);
    restart_script(script);
    CHECK(!script->lerpActive);
    kill_script(script);
    CHECK(gNumScripts == 0);
    expect_trace("L");
}

static void test_kill_frees_args(void) {
    Evt* parent;
    Evt* child;

    reset_test();
    parent = start_test_script(&EVS_TestArgsKill);
    evt_execute_next_command(parent);
    child = find_script_by_id(parent->varTable[0]);
    CHECK(child != nullptr);
    CHECK(child->argCount == 2);
    CHECK(child->argVars != nullptr);
    gExpectedHeapFree = child->argVars;
    kill_script(parent);
    CHECK(gExpectedHeapFreeSeen);
    CHECK(gNumScripts == 0);
    expect_trace("AP");
}

static void test_interpreter_behavior(void) {
    EvtScript* scripts[] = {
        &EVS_TestArithmetic,
        &EVS_TestControlFlow,
        &EVS_TestStorage,
        &EVS_TestEval,
        &EVS_TestArgsParent,
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(scripts); i++) {
        s32 frame;

        reset_test();
        evt_execute_next_command(start_test_script(scripts[i]));
        for (frame = 0; frame < 100 && gNumScripts != 0; frame++) {
            update_scripts();
        }
        CHECK(gNumScripts == 0);
        if (gNumScripts != 0) {
            kill_all_scripts();
        }
    }
}

static void test_scheduler_behavior(void) {
    s32 i;

    reset_test();
    start_test_script(&EVS_TestScheduler);
    for (i = 0; i < 5 && gNumScripts != 0; i++) {
        update_scripts();
    }
    CHECK(gNumScripts == 0);
    expect_trace("pTCQ");

    reset_test();
    start_test_script(&EVS_TestLerp);
    for (i = 0; i < 5 && gNumScripts != 0; i++) {
        update_scripts();
    }
    CHECK(gNumScripts == 0);
    CHECK(gLerpIterations == 3);
}

int main(int argc, char** argv) {
    gCurrentScriptListPtr = &gTestScriptList;
    gMapVars = gTestMapVars;
    gMapFlags = gTestMapFlags;

    if (argc == 2 && strcmp(argv[1], "--error-finalizer") == 0) {
        reset_test();
        kill_script(start_test_script(&EVS_ErrorFinally));
        fprintf(stderr, "FAIL: error-returning finalizer did not panic\n");
        return 1;
    }
    if (argc == 2 && strcmp(argv[1], "--exec-wait-finalizer") == 0) {
        reset_test();
        kill_script(start_test_script(&EVS_ExecWaitFinally));
        fprintf(stderr, "FAIL: ExecWait inside a finalizer did not panic\n");
        return 1;
    }
    if (argc == 2 && strcmp(argv[1], "--call-start-owned-finalizer") == 0) {
        reset_test();
        kill_script(start_test_script(&EVS_CallStartsOwnedFinally));
        fprintf(stderr, "FAIL: a finalizer Call started an owned child\n");
        return 1;
    }

    test_interpreter_behavior();
    test_scheduler_behavior();
    test_natural_matrix();
    test_forced_matrix();
    test_exec_wait_copyback();
    test_detached_companion();
    test_self_kill();
    test_cycle();
    test_child_kills_parent(&EVS_ChildKillsParent, "CcP");
    test_child_kills_parent(&EVS_ChildKillsParentNoFinally, "Cc");
    test_blocking_child_kills_parent();
    test_active_caller_is_killed();
    test_sibling_cleanup_mutates_child_list();
    test_normal_command_can_replace_terminating_self();
    test_finalizer_can_start_detached_scripts();
    test_kill_all_rescans_for_spawned_scripts();
    test_kill_all_from_active_command();
    test_clear_script_list_bypasses_finalizers();
    test_kill_blocked_call();
    test_kill_suspended_tree();
    test_jump_restarts_script();
    test_restart_clears_lerp_state();
    test_kill_frees_args();

    if (gFailures != 0) {
        fprintf(stderr, "%ld runtime test(s) failed\n", gFailures);
        return 1;
    }
    puts("All EVT runtime tests passed.");
    return 0;
}
