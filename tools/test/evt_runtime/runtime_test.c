#include "common.h"
#include "bound_script.h"
#include "hud_element.h"

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
EncounterStatus gCurrentEncounter;
BattleStatus gBattleStatus;
s32 gEncounterState = ENCOUNTER_STATE_NONE;
s32 gTimeFreezeMode = TIME_FREEZE_NONE;
HudScript HES_HPDigit0 = { 0 };
HudScript HES_HPDigit1 = { 0 };
HudScript HES_HPDigit2 = { 0 };
HudScript HES_HPDigit3 = { 0 };
HudScript HES_HPDigit4 = { 0 };
HudScript HES_HPDigit5 = { 0 };
HudScript HES_HPDigit6 = { 0 };
HudScript HES_HPDigit7 = { 0 };
HudScript HES_HPDigit8 = { 0 };
HudScript HES_HPDigit9 = { 0 };
static void* gExpectedHeapFree;
static b32 gExpectedHeapFreeSeen;
static s32 gTestGlobalFlags[2048];
static s32 gTestAreaFlags[256];
static s8 gTestGlobalBytes[512];
static s8 gTestAreaBytes[16];
static Evt* gOwnerToReplace;

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

void set_defeated(s32 mapID, s32 encounterID) {
}

void create_encounters(void) {
}

void update_encounters_neutral(void) {
}

void update_encounters_pre_battle(void) {
}

void update_encounters_conversation(void) {
}

void update_encounters_post_battle(void) {
}

void update_merlee_messages(void) {
}

s32 spr_free_sprite(s32 spriteInstanceID) {
    return 0;
}

s32 spr_load_npc_sprite(s32 animID, AnimID* limitAnimList) {
    return 0;
}

void delete_shadow(s32 shadowIndex) {
}

s32 create_shadow_type(s32 type, f32 x, f32 y, f32 z) {
    return 0;
}

void remove_effect(void* effect) {
}

void remove_actor_decoration(Actor* actor, s32 decorationIndex) {
}

void set_actor_glow_pal(Actor* actor, s32 arg1) {
}

void set_npc_imgfx_all(s32 arg0, ImgFXType arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
}

void remove_all_status_icons(s32 hudElementDataIndex) {
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
extern EvtScript EVS_ActorOwnerCompanion;
extern EvtScript EVS_ActorRebound;
extern EvtScript EVS_EnemyRebound;

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
    start_script(&EVS_Companion, EVT_PRIORITY_0, 0);
    return ApiStatus_DONE2;
}

static API_CALLABLE(ReplaceOwner) {
    Evt* replacement;

    kill_script(gOwnerToReplace);
    replacement = start_script(&EVS_Companion, EVT_PRIORITY_0, 0);
    replacement->groupFlags = script->groupFlags;
    return ApiStatus_DONE2;
}

static API_CALLABLE(DeleteEnemyOwner) {
    kill_enemy(script->owner1.enemy);
    return ApiStatus_DONE1;
}

static API_CALLABLE(VerifyEnemyOwner) {
    Enemy* enemy = script->owner1.enemy;

    CHECK(get_enemy(enemy->npcID) == enemy);
    CHECK(get_npc_safe(script->owner2.npcID) != nullptr);
    CHECK(enemy->deletePending);
    CHECK(enemy->flags & ENEMY_FLAG_DISABLE_AI);
    return Record(script, isInitialCall);
}

static API_CALLABLE(RebindEnemyOwner) {
    Enemy* enemy = script->owner1.enemy;
    Evt* replacement = start_script(&EVS_EnemyRebound, EVT_PRIORITY_0, 0);

    set_bound_script_live(&enemy->scripts.ai, replacement);
    replacement->owner1.enemy = enemy;
    replacement->owner2.npcID = enemy->npcID;
    return Record(script, isInitialCall);
}

static API_CALLABLE(DeleteActorOwner) {
    btl_delete_actor(get_actor(script->owner1.actorID));
    return ApiStatus_DONE2;
}

static API_CALLABLE(VerifyActorOwner) {
    Actor* actor = get_actor(script->owner1.actorID);

    CHECK(actor != nullptr);
    if (actor != nullptr) {
        CHECK(actor->deletePending);
    }
    return Record(script, isInitialCall);
}

static API_CALLABLE(RebindActorOwner) {
    Actor* actor = get_actor(script->owner1.actorID);
    Evt* replacement = start_script(&EVS_ActorRebound, EVT_PRIORITY_0, 0);

    set_bound_script_live(&actor->scripts.handleEvent, replacement);
    replacement->owner1.actorID = script->owner1.actorID;
    return Record(script, isInitialCall);
}

static API_CALLABLE(KillAllFromCall) {
    kill_all_scripts();
    return ApiStatus_DONE2;
}

static API_CALLABLE(InvalidateScriptContext) {
    clear_script_list();
    heap_free(script);
    return VmStatus_INVALID;
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

EvtScript EVS_ReplaceOwnerChild = {
    Call(ReplaceOwner)
    Call(Record, 'X')
    Finally
        Call(Record, 'C')
    End
};

EvtScript EVS_ReplaceOwnerFromChild = {
    ExecWait(EVS_ReplaceOwnerChild)
    Call(Record, 'X')
    Finally
        Call(Record, 'P')
    End
};

EvtScript EVS_EnemyOwnerCompanion = {
    Wait(100)
    Finally
        Call(Record, 'D')
    End
};

EvtScript EVS_DeleteEnemyOwner = {
    ChildThread
        Wait(100)
        Finally
            Call(VerifyEnemyOwner, 'C')
        EndChildThread
    Call(DeleteEnemyOwner)
    Call(Record, 'X')
    Finally
        Call(VerifyEnemyOwner, 'P')
        Exec(EVS_EnemyOwnerCompanion)
    End
};

EvtScript EVS_EnemyOwnedSlot = {
    Wait(100)
    Finally
        Call(VerifyEnemyOwner, 'S')
    End
};

EvtScript EVS_EnemyRebindRoot = {
    Wait(100)
    Finally
        Call(RebindEnemyOwner, 'A')
    End
};

EvtScript EVS_EnemyRebound = {
    Wait(100)
    Finally
        Call(VerifyEnemyOwner, 'B')
    End
};

EvtScript EVS_EnemyBindingWait = {
    Wait(100)
    End
};

EvtScript EVS_ActorOwnerCompanion = {
    Wait(100)
    Finally
        Call(Record, 'D')
    End
};

EvtScript EVS_DeleteActorOwner = {
    ChildThread
        Wait(100)
        Finally
            Call(VerifyActorOwner, 'C')
        EndChildThread
    Call(DeleteActorOwner)
    Call(Record, 'X')
    Finally
        Call(VerifyActorOwner, 'P')
        Exec(EVS_ActorOwnerCompanion)
    End
};

EvtScript EVS_ActorOwnedSlot = {
    Wait(100)
    Finally
        Call(VerifyActorOwner, 'S')
    End
};

EvtScript EVS_ActorRebindRoot = {
    Wait(100)
    Finally
        Call(RebindActorOwner, 'A')
    End
};

EvtScript EVS_ActorRebound = {
    Wait(100)
    Finally
        Call(VerifyActorOwner, 'B')
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

EvtScript EVS_InvalidateFromCall = {
    Call(InvalidateScriptContext)
    Call(Record, 'X')
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
    memset(&gCurrentEncounter, 0, sizeof(gCurrentEncounter));
    memset(&gBattleStatus, 0, sizeof(gBattleStatus));
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
    gOwnerToReplace = nullptr;
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

static Enemy* create_test_enemy(Encounter** encounterOut, s32 npcID) {
    NpcBlueprint npcBlueprint = {
        .flags = NPC_FLAG_HAS_NO_SPRITE,
    };
    Encounter* encounter = calloc(1, sizeof(*encounter));
    Enemy* enemy = heap_malloc(sizeof(*enemy));
    s32 npcIndex;
    Npc* npc;

    init_npc_list();
    npcIndex = create_basic_npc(&npcBlueprint);
    npc = get_npc_by_index(npcIndex);
    npc->npcID = npcID;

    encounter->count = 1;
    encounter->enemy[0] = enemy;
    enemy->flags = ENEMY_FLAG_PASSIVE;
    enemy->encounterIndex = 0;
    enemy->npcID = npcID;
    gCurrentEncounter.numEncounters = 1;
    gCurrentEncounter.encounterList[0] = encounter;
    gExpectedHeapFree = enemy;
    *encounterOut = encounter;
    return enemy;
}

Actor* get_actor(s32 actorID) {
    switch (actorID & ACTOR_CLASS_MASK) {
        case ACTOR_CLASS_PLAYER:
            return gBattleStatus.playerActor;
        case ACTOR_CLASS_PARTNER:
            return gBattleStatus.partnerActor;
        case ACTOR_CLASS_ENEMY:
            return gBattleStatus.enemyActors[(u8) actorID];
    }
    return nullptr;
}

static Actor* create_test_actor(s32 actorID) {
    Actor* actor = heap_malloc(sizeof(*actor));

    actor->actorID = actorID;
    if ((actorID & ACTOR_CLASS_MASK) == ACTOR_CLASS_PARTNER) {
        gBattleStatus.partnerActor = actor;
    } else {
        gBattleStatus.enemyActors[(u8) actorID] = actor;
    }
    gExpectedHeapFree = actor;
    return actor;
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

static void test_active_child_can_replace_owner(void) {
    Evt* parent;
    Evt* child;
    Evt* replacement;
    s32 i;

    reset_test();
    parent = start_test_script(&EVS_ReplaceOwnerFromChild);
    parent->groupFlags = 17;
    evt_execute_next_command(parent);
    child = parent->blockingChild;
    CHECK(child != nullptr);
    gOwnerToReplace = parent;
    evt_execute_next_command(child);
    CHECK(gNumScripts == 1);
    replacement = nullptr;
    for (i = 0; i < MAX_SCRIPTS; i++) {
        if ((*gCurrentScriptListPtr)[i] != nullptr) {
            replacement = (*gCurrentScriptListPtr)[i];
            break;
        }
    }
    CHECK(replacement != nullptr);
    CHECK(replacement->groupFlags == 17);
    expect_trace("CP");
    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("CPC");
}

static void test_enemy_deletion_preserves_detached_scripts(void) {
    Encounter* encounter;
    Enemy* enemy;
    Evt* script;
    s32 npcID = 100;

    reset_test();
    enemy = create_test_enemy(&encounter, npcID);
    gCurrentEncounter.curEnemy = enemy;
    script = start_test_script(&EVS_DeleteEnemyOwner);
    script->owner1.enemy = enemy;
    script->owner2.npcID = enemy->npcID;
    set_bound_script_live(&enemy->scripts.init, script);
    evt_execute_next_command(script);
    CHECK(!gExpectedHeapFreeSeen);
    CHECK(gNumScripts == 1);
    CHECK(encounter->enemy[0] == enemy);
    check_all_scripts_detached(1);
    expect_trace("CP");
    kill_enemy(enemy);
    update_encounters();
    CHECK(gExpectedHeapFreeSeen);
    CHECK(gNumScripts == 1);
    CHECK(encounter->enemy[0] == nullptr);
    CHECK(gCurrentEncounter.curEnemy == nullptr);
    CHECK(get_npc_safe(npcID) == nullptr);
    expect_trace("CP");
    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("CPD");
    free(encounter);
    gExpectedHeapFree = nullptr;
}

static void test_enemy_deletion_finalizes_all_registered_slots(void) {
    Encounter* encounter;
    Enemy* enemy;
    s32 npcID = 101;
    s32 i;

    reset_test();
    enemy = create_test_enemy(&encounter, npcID);
    for (i = 0; i < ARRAY_COUNT(enemy->scripts.all); i++) {
        Evt* script = start_test_script(&EVS_EnemyOwnedSlot);

        script->owner1.enemy = enemy;
        script->owner2.npcID = npcID;
        set_bound_script_live(&enemy->scripts.all[i], script);
    }

    kill_enemy(enemy);
    CHECK(!gExpectedHeapFreeSeen);
    CHECK(gNumScripts == 0);
    CHECK(encounter->enemy[0] == enemy);
    expect_trace("SSSSSS");

    update_encounters();
    CHECK(gExpectedHeapFreeSeen);
    CHECK(encounter->enemy[0] == nullptr);
    CHECK(get_npc_safe(npcID) == nullptr);
    free(encounter);
    gExpectedHeapFree = nullptr;
}

static void test_enemy_deletion_terminates_finalizer_rebinding(void) {
    Encounter* encounter;
    Enemy* enemy;
    Evt* script;
    s32 npcID = 102;

    reset_test();
    enemy = create_test_enemy(&encounter, npcID);
    script = start_test_script(&EVS_EnemyRebindRoot);
    script->owner1.enemy = enemy;
    script->owner2.npcID = npcID;
    set_bound_script_live(&enemy->scripts.ai, script);

    kill_enemy(enemy);
    CHECK(!gExpectedHeapFreeSeen);
    CHECK(gNumScripts == 0);
    CHECK(encounter->enemy[0] == enemy);
    expect_trace("AB");

    update_encounters();
    CHECK(gExpectedHeapFreeSeen);
    CHECK(encounter->enemy[0] == nullptr);
    CHECK(get_npc_safe(npcID) == nullptr);
    free(encounter);
    gExpectedHeapFree = nullptr;
}

static void test_enemy_bindings_set_npc_owner(void) {
    Encounter* encounter;
    Enemy* enemy;
    Evt* script;
    s32 npcID = 103;

    reset_test();
    enemy = create_test_enemy(&encounter, npcID);

    script = get_script_by_id(bind_enemy_ai(enemy, &EVS_EnemyBindingWait));
    CHECK(script->owner1.enemy == enemy);
    CHECK(script->owner2.npcID == npcID);
    script = get_script_by_id(bind_enemy_aux(enemy, &EVS_EnemyBindingWait));
    CHECK(script->owner1.enemy == enemy);
    CHECK(script->owner2.npcID == npcID);
    script = get_script_by_id(bind_enemy_interact(enemy, &EVS_EnemyBindingWait));
    CHECK(script->owner1.enemy == enemy);
    CHECK(script->owner2.npcID == npcID);

    kill_enemy(enemy);
    CHECK(gNumScripts == 0);
    expect_trace("");
    update_encounters();
    CHECK(gExpectedHeapFreeSeen);
    free(encounter);
    gExpectedHeapFree = nullptr;
}

static void test_actor_self_deletion_retains_owner_until_finally(void) {
    Actor* actor;
    Evt* script;
    s32 actorID = ACTOR_ENEMY0;

    reset_test();
    actor = create_test_actor(actorID);
    script = start_test_script(&EVS_DeleteActorOwner);
    script->owner1.actorID = actorID;
    set_bound_script_live(&actor->scripts.handleEvent, script);

    evt_execute_next_command(script);
    CHECK(!gExpectedHeapFreeSeen);
    CHECK(actor->deletePending);
    CHECK(get_actor(actorID) == actor);
    CHECK(gNumScripts == 1);
    check_all_scripts_detached(1);
    expect_trace("CP");

    // This is the same retry performed for pending actors at the start of btl_update.
    btl_delete_actor(actor);
    CHECK(gExpectedHeapFreeSeen);
    CHECK(get_actor(actorID) == nullptr);
    CHECK(gNumScripts == 1);
    expect_trace("CP");

    kill_all_scripts();
    CHECK(gNumScripts == 0);
    expect_trace("CPD");
    gExpectedHeapFree = nullptr;
}

static void test_actor_deletion_finalizes_all_registered_slots(void) {
    Actor* actor;
    s32 actorID = ACTOR_ENEMY1;
    s32 i;

    reset_test();
    actor = create_test_actor(actorID);
    for (i = 0; i < ARRAY_COUNT(actor->scripts.all); i++) {
        Evt* script = start_test_script(&EVS_ActorOwnedSlot);

        script->owner1.actorID = actorID;
        set_bound_script_live(&actor->scripts.all[i], script);
    }

    btl_delete_actor(actor);
    CHECK(gExpectedHeapFreeSeen);
    CHECK(get_actor(actorID) == nullptr);
    CHECK(gNumScripts == 0);
    expect_trace("SSSS");
    gExpectedHeapFree = nullptr;
}

static void test_actor_deletion_terminates_finalizer_rebinding(void) {
    Actor* actor;
    Evt* script;
    s32 actorID = ACTOR_ENEMY2;

    reset_test();
    actor = create_test_actor(actorID);
    script = start_test_script(&EVS_ActorRebindRoot);
    script->owner1.actorID = actorID;
    set_bound_script_live(&actor->scripts.handleEvent, script);

    btl_delete_actor(actor);
    CHECK(gExpectedHeapFreeSeen);
    CHECK(get_actor(actorID) == nullptr);
    CHECK(gNumScripts == 0);
    expect_trace("AB");
    gExpectedHeapFree = nullptr;
}

static void test_partner_deletion_remains_synchronous(void) {
    Actor* partner;

    reset_test();
    partner = create_test_actor(ACTOR_PARTNER);
    btl_delete_actor(partner);
    CHECK(gExpectedHeapFreeSeen);
    CHECK(gBattleStatus.partnerActor == nullptr);
    CHECK(gNumScripts == 0);
    gExpectedHeapFree = nullptr;
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

static void test_active_command_invalidates_context(void) {
    Evt* script;

    reset_test();
    gTestGameStatus.context = CONTEXT_WORLD;
    clear_script_list();
    script = start_test_script(&EVS_InvalidateFromCall);
    CHECK(evt_execute_next_command(script) == EVT_CMD_RESULT_YIELD);
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
    test_active_child_can_replace_owner();
    test_enemy_deletion_preserves_detached_scripts();
    test_enemy_deletion_finalizes_all_registered_slots();
    test_enemy_deletion_terminates_finalizer_rebinding();
    test_enemy_bindings_set_npc_owner();
    test_actor_self_deletion_retains_owner_until_finally();
    test_actor_deletion_finalizes_all_registered_slots();
    test_actor_deletion_terminates_finalizer_rebinding();
    test_partner_deletion_remains_synchronous();
    test_finalizer_can_start_detached_scripts();
    test_kill_all_rescans_for_spawned_scripts();
    test_kill_all_from_active_command();
    test_clear_script_list_bypasses_finalizers();
    test_active_command_invalidates_context();
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
