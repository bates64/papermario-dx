# EVT Plus

EVT Plus adds quality-of-life features which make EVT scripts more robust and readable. Its goal is to provide direct support for patterns which previously required substantial boilerplate or `Goto`-based control flow.

The primary features are:

- optional compile-time EvtScript validation
- arguments for `Exec`, `ExecGetID`, and `ExecWait`, read through `ArgVar`
- expanded arithmetic expressions such as `A = B + C + D`, `A = B / C`, and `A = clamp(B, MIN, MAX)`
- lightweight inline calls to C helpers through `Eval`, `Invoke`, and their variants
- range conditions with `IfRange` and `IfNotRange`
- greater loop iteration control with `ContinueLoop` and `RetryLoop`
- first-class lerp loops with `Lerp` and `EndLerp`
- guaranteed cleanup blocks with `Finally`
- commands for awaiting child threads or a single script ID
- vector convenience macros for adjacent EVT variables
- variadic buffer reads with `BufRead` and `FBufRead`
- clearer command names with compatibility aliases
- smaller bytecode by packing the opcode, argument count, and line number into one command header

## Contents

- [Preview](#preview)
  - [Example: Pass Work to Another Script](#example-pass-work-to-another-script)
  - [Example: Use Small C Helpers Directly](#example-use-small-c-helpers-directly)
  - [Example: Keep Cleanup Reliable](#example-keep-cleanup-reliable)

1. [Compile-Time Validation](#1-compile-time-validation)
2. [Exec with Arguments](#2-exec-with-arguments)
    - [Literal by Default](#literal-by-default)
    - [ArgVars are Read-Only](#argvars-are-read-only)
    - [ArgVars are Not Passed to Grandchildren](#argvars-are-not-passed-to-grandchildren)
3. [Variadic Arithmetic](#3-variadic-arithmetic)
    - [Add and AddF](#add-and-addf)
    - [Mul and MulF](#mul-and-mulf)
    - [Sub, Div, and Mod](#sub-div-and-mod)
    - [Neg, Abs, and Sign](#neg-abs-and-sign)
    - [Min, Max, and Clamp](#min-max-and-clamp)
4. [Eval and Invoke](#4-eval-and-invoke)
    - [Example: Return Values](#example-return-values)
    - [Example: Quick Calls to C](#example-quick-calls-to-c)
    - [Example: Branch on Predicate](#example-branch-on-predicate)
    - [Supported Signatures](#supported-signatures)
    - [When to Use Call](#when-to-use-call)
5. [Vector Helpers](#5-vector-helpers)
    - [Passing Vectors](#passing-vectors)
    - [Setting and Manipulating Vectors](#setting-and-manipulating-vectors)
6. [Named Labels](#6-named-labels)
7. [Stricter Case Groups](#7-stricter-case-groups)
8. [If Ranges](#8-if-ranges)
9. [Loop Control](#9-loop-control)
    - [ContinueLoop](#continueloop)
    - [RetryLoop](#retryloop)
10. [Lerp Loops](#10-lerp-loops)
11. [Finally Blocks](#11-finally-blocks)
    - [Cleanup Order](#cleanup-order)
    - [Restrictions](#restrictions)
    - [NPC_SELF and ACTOR_SELF](#npc_self-and-actor_self)
12. [Awaiting Scripts](#12-awaiting-scripts)
13. [Packed Command Headers](#13-packed-command-headers)
14. [Buffer Reads](#14-buffer-reads)
15. [Command Renames](#15-command-renames)

- [Additional Ideas](#additional-ideas)

## Preview

The additions in EVT Plus are small on their own, but they are designed to work together. The following examples show how they simplify common script patterns.

### Example: Pass Work to Another Script

Suppose we want to execute a detached worker script and wait for it to finish its work. In vanilla EVT, you have to poll its script ID in a busy-wait loop. You could also 'pass' values to the worker implicitly because the new script receives a copy of its parent's local variables. The parent must reserve those variables for inputs and remember not to reuse them:

```c
EvtScript N(EVS_JumpWorker) = {
    Call(NpcJump1, LVar0, LVar1, LVar2, LVar3, 20)
    Return
    End
};

EvtScript N(EVS_Example_WaitForWork) = {
    // launch a detached worker
    Set(LVar0, NPC_Bob)
    Set(LVar1, 120)
    Set(LVar2, 0)
    Set(LVar3, -60)
    ExecGetTID(N(EVS_JumpWorker), LVarA)

    // do something else
    Call(DoSomethingElse)

    // wait for the worker to finish
    Label(0)
        IsThreadRunning(LVarA, LVarB)
        IfEq(LVarB, true)
            Wait(1)
            Goto(0)
        EndIf
    Return
    End
};
```

With script arguments and `AwaitScript`, the inputs and the wait are both clear and explicit:

```c
EvtScript N(EVS_JumpWorker) = {
    ExpectArgs(4)
    Call(NpcJump1, ArgVar0, ArgVar1, ArgVar2, ArgVar3, 20)
    Return
    End
};

EvtScript N(EVS_Example_WaitForWork) = {
    ExecGetID(LVarA, N(EVS_JumpWorker), NPC_Bob, 120, 0, -60)
    Call(DoSomethingElse)
    AwaitScript(LVarA)
    Return
    End
};
```

### Example: Use Small C Helpers Directly

Vanilla EVT needs an `API_CALLABLE` wrapper and a temporary output variable to ask a small C helper a question:

```c
API_CALLABLE(N(IsNear)) {
    Bytecode* args = script->ptrReadPos;
    f32 ax = evt_get_float_variable(script, *args++);
    f32 ay = evt_get_float_variable(script, *args++);
    f32 az = evt_get_float_variable(script, *args++);
    f32 bx = evt_get_float_variable(script, *args++);
    f32 by = evt_get_float_variable(script, *args++);
    f32 bz = evt_get_float_variable(script, *args++);
    Bytecode outVar = *args++;
    f32 dx = ax - bx;
    f32 dy = ay - by;
    f32 dz = az - bz;

    evt_set_variable(script, outVar, SQ(dx) + SQ(dy) + SQ(dz) < SQ(60.0f));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_Example_AwaitNearby) = {
    ...
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(GetNpcPos, NPC_Bob, LVar3, LVar4, LVar5)
    Call(N(IsNear), LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, LVarA)
    IfEq(LVarA, true)
        ...
    EndIf
    ...
}
```

With `IfEvalF` and the vector helpers, the C function has an ordinary signature and the script can use its result directly:

```c
b32 N(IsNear)(f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz) {
    f32 dx = ax - bx;
    f32 dy = ay - by;
    f32 dz = az - bz;

    return SQ(dx) + SQ(dy) + SQ(dz) < SQ(60.0f);
}

EvtScript N(EVS_Example_AwaitNearby) = {
    ...
    Call(GetPlayerPos, EVT_AS_VEC3(LVar0))
    Call(GetNpcPos, NPC_Bob, EVT_AS_VEC3(LVar3))
    IfEvalF(N(IsNear), EVT_AS_VEC3(LVar0), EVT_AS_VEC3(LVar3))
        ...
    EndIf
    ...
}
```

### Example: Keep Cleanup Reliable

A script which disables player input and creates a persistent effect owns both until it finishes. Every early return must either repeat the cleanup or use a `Goto` to a shared cleanup block. Neither option is safe if the script is killed externally or the programmer forgets to cover a return path, leaking resources and state:

```c
EvtScript N(EVS_Example_NeedsCleanup) = {
    // both of these require cleanup
    Call(DisablePlayerInput, true)
    PlayEffect(EFFECT_LIGHT_RAYS, 2, 0, 40, 0, Float(1.0), LVarA, 0)

    // possible early-return
    Call(ShouldSkipAnimation, LVar0)
    IfEq(LVar0, true)
        Call(RemoveEffect, LVarA)
        Call(DisablePlayerInput, false)
        Return
    EndIf

    // do some work, using lerp as an example
    // this vanilla Lerp machinery clobbers LVar0, LVar1, LVarB, LVarC, LVarD, LVarE, and LVarF
    Call(MakeLerp, 0, 90, 20, EASING_COS_IN_OUT)
    Loop(0)
        Call(UpdateLerp)
        Call(RotateModel, MODEL_door, LVar0, 0, 1, 0)
        IfEq(LVar1, false)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop

    // end-of-script cleanup
    Call(RemoveEffect, LVarA)
    Call(DisablePlayerInput, false)
    Return
    End
};
```

With EVT Plus, `Return` only describes the decision to stop. We use `Finally` to safely remove the effect and restore input. This cleanup occurs even if the script is killed by another script or from the engine:

```c
EvtScript N(EVS_Example_NeedsCleanup) = {
    // both of these require cleanup
    Call(DisablePlayerInput, true)
    PlayEffect(EFFECT_LIGHT_RAYS, 2, 0, 40, 0, Float(1.0), LVarF, 0)

    // early Return automatically enters Finally
    Call(ShouldSkipAnimation, LVar0)
    IfEq(LVar0, true)
        Return
    EndIf

    // do some work using first-class Lerp support
    // this new version only writes to the chosen LVar
    // we do not need to worry about accidently overwriting the effect handle on LVarF
    Lerp(LVar0, 0, 90, 20, EASING_COS_IN_OUT)
        Call(RotateModel, MODEL_door, LVar0, 0, 1, 0)
    EndLerp

    // shared guaranteed cleanup
    Finally
        Call(RemoveEffect, LVarF)
        Call(DisablePlayerInput, false)
    End
};
```

## 1. Compile-Time Validation

A compile-time structural validator for EvtScripts lives in `tools/build/evt_validate_obj.py`. It can be disabled globally, and individual scripts can opt out by not following the `EVS_*` naming convention.

The validator catches malformed scripts, unsafe control flow, and patterns which are technically valid but likely unintended:

- missing `End`
- commands after `End`
- unknown opcodes
- malformed or truncated commands
- wrong argument counts
- unclosed or mismatched `If`/`Else`/`EndIf`
- unclosed or mismatched `Loop`/`EndLoop`
- unclosed, mismatched, or nested `Lerp`/`EndLerp`
- unclosed or mismatched `Switch`/`EndSwitch`
- loop and switch nesting deeper than runtime limits
- invalid case groups
- `BreakLoop` outside loops or lerp loops
- `ContinueLoop` or `RetryLoop` outside loops, or inside a lerp loop
- `BreakSwitch` or `Case` outside switches
- unclosed `Thread` or `ChildThread` blocks
- duplicate labels
- label counts beyond runtime limits
- `Goto` with no matching label
- invalid string label references
- invalid `Exec` args
- invalid functions for `Eval`/`Invoke`
- mixed integer and `Float(...)` literal bounds in `IfRange`/`IfNotRange`
- invalid integer/float literals in arithmetic commands
- literal `Clamp`/`ClampF` bounds where min is greater than max
- literal `Lerp` durations less than zero
- invalid `Finally` blocks

The validator has its own focused test suite:

```sh
python3 tools/test/evt_validator.py
```

Fixtures live in:

- `tools/test/evt_validator/pass/` for scripts that should compile and validate
- `tools/test/evt_validator/fail/` for scripts that should fail validation
- each fail test has a `.stderr` with expected error messages

A host-side runtime test, compiled with sanitizers, covers interpreter and script-lifecycle behavior. It first runs the whole-project `validate_evt_us` target, then executes focused scripts covering ordinary VM behavior and termination:

```sh
python3 tools/test/evt_runtime.py
```

## 2. Exec with Arguments

`Exec`, `ExecGetID`, and `ExecWait` can now pass arguments to the new script. It reads them through `ArgVar(index)` or the shorthand names `ArgVar0` through `ArgVar7`. Argument storage is allocated as needed, allowing roughly 250 arguments after the command's own operands.

For clarity, `ExecGetID` places its output first: `ExecGetID(outVar, source, args...)`. The legacy `ExecGetTID(source, outVar, args...)` form keeps its original ordering for compatibility.

```c
EvtScript N(EVS_Child) = {
    ExpectArgs(3)
    Call(SetNpcPos, NPC_SELF, ArgVar0, ArgVar1, ArgVar2)
    Return
    End
};

EvtScript N(EVS_Parent) = {
    Exec(N(EVS_Child), 100, 20, -50)
    Return
    End
};
```

`ExpectArgs(NUM_ARGS)` documents the expected argument count and catches mismatches with a runtime assertion.

### Literal by Default

An argument may be a variable, a constant, or an encoded value such as a pointer. To preserve that distinction, arguments are passed as literal words by default:

```c
Set(LVar0, 12)
Exec(N(EVS_Child), LVar0) // child ArgVar0 is 0xFE363C80 (LVar0)
```

The child receives the literal encoded word `LVar0`, not the current value `12`. That preserves pointer constants, variable identifiers, refs, and other EVT bytecode values exactly as written.

When you want the current integer value of an expression, wrap it with `ARG_INT`:

```c
Set(LVar0, 12)
Exec(N(EVS_Child), ARG_INT(LVar0)) // child ArgVar0 is 12
```

When you want the current float value of an expression, wrap it with `ARG_FLOAT`:

```c
SetF(LVar1, Float(1.5))
Exec(N(EVS_Child), ARG_FLOAT(LVar1)) // child ArgVar0 is Float(1.5)
```

The child can use the wrapped fixed-point value like any other float expression:

```c
EvtScript N(EVS_Child) = {
    ExpectArgs(1)
    AddF(LVar0, ArgVar0)
    Return
    End
};
```

### ArgVars are Read-Only

`ArgVar` values are intended to be call inputs. Reading them is fine; writing to them is not. `evt_set_variable` and `evt_set_float_variable` will panic if asked to write to an ArgVar.

Copy them to an LVar if the child needs a mutable working copy:

```c
Set(LVar0, ArgVar0)
Add(LVar0, 1)
```

Normal EVT variable access treats ArgVars as immutable. C code should not write directly to their backing storage.

### ArgVars are Not Passed to Grandchildren

Unlike LVars, ArgVars are not copied to grandchildren or returned to the parent. They remain stable inputs for the lifetime of the script which received them.

## 3. Variadic Arithmetic

The original arithmetic commands mutate their destination, so calculating a value from several inputs normally takes multiple commands:

```c
Set(LVar0, LVar1)
Add(LVar0, LVar2)
Add(LVar0, 10)
```

Variadic arithmetic expresses the same calculation in one command, without using the destination as temporary storage:

```c
Add(LVar0, LVar1, LVar2, 10)
```

### Add and AddF

Two arguments preserve the old behavior:

```c
Add(LVar0, 5)  // LVar0 += 5
AddF(LVar1, Float(0.5))
```

More than two arguments add all inputs and store the result:

```c
Add(LVar0, LVar1, LVar2, 10)                // LVar0 = LVar1 + LVar2 + 10
AddF(LVar3, LVar4, Float(1.0), Float(2.0))  // LVar3 = LVar4 + 1.0 + 2.0
```

In the expression form, the first argument is only the destination and is not included in the sum.

### Mul and MulF

Two arguments preserve the old behavior:

```c
Mul(LVar0, 2)  // LVar0 *= 2
MulF(LVar1, Float(0.5))
```

More than two arguments multiply all inputs and store the result:

```c
Mul(LVar0, LVar1, 3, 4)                     // LVar0 = LVar1 * 3 * 4
MulF(LVar2, Float(2.0), Float(3.0), LVar3)  // LVar2 = 2.0 * 3.0 * LVar3
```

### Sub, Div, and Mod

Two arguments preserve the old behavior:

```c
Sub(LVar0, 5)   // LVar0 -= 5
Div(LVar1, 2)   // LVar1 /= 2
Mod(LVar2, 10)  // LVar2 %= 10
```

Three arguments compute from two input expressions:

```c
Sub(LVar0, LVar1, LVar2)  // LVar0 = LVar1 - LVar2
Div(LVar0, LVar1, 2)      // LVar0 = LVar1 / 2
Mod(LVar0, LVar1, 10)     // LVar0 = LVar1 % 10

SubF(LVar0, LVar1, Float(1.0))
DivF(LVar0, LVar1, Float(2.0))
```

### Neg, Abs, and Sign

Unary math commands support both mutating and expression forms:

```c
Neg(LVar0)          // LVar0 = -LVar0
Neg(LVar0, LVar1)   // LVar0 = -LVar1

Abs(LVar2)          // LVar2 = abs(LVar2)
Abs(LVar2, LVar3)   // LVar2 = abs(LVar3)

Sign(LVar4)         // LVar4 = sign(LVar4), as -1, 0, or 1
Sign(LVar4, LVar5)  // LVar4 = sign(LVar5)
```

Float variants are available for fixed-point values:

```c
NegF(LVar0, Float(5.0))
AbsF(LVar1, LVar2)
SignF(LVar3)
```

### Min, Max, and Clamp

`Min` and `Max` support a mutating two-argument form, plus expression forms with two or more inputs:

```c
Min(LVar0, 10)              // LVar0 = min(LVar0, 10)
Min(LVar0, LVar1, LVar2)    // LVar0 = min(LVar1, LVar2)
Min(LVar0, LVar1, 20, 30)   // LVar0 = min(LVar1, 20, 30)

Max(LVar3, 10)
Max(LVar3, LVar4, LVar5)
```

`Clamp` supports mutating and expression forms:

```c
Clamp(LVar0, 0, 100)           // LVar0 = clamp(LVar0, 0, 100)
Clamp(LVar0, LVar1, 0, 100)    // LVar0 = clamp(LVar1, 0, 100)
```

Float variants are available for fixed-point values:

```c
MinF(LVar0, LVar1, Float(0.0))
MaxF(LVar2, LVar3, Float(100.0))
ClampF(LVar4, Float(0.0), Float(1.0))
```

The integer commands should use integer literals. The validator rejects obvious uses of `Float(...)` with integer-only commands when a float variant exists. `Clamp` and `ClampF` also reject literal ranges where the min bound is greater than the max bound.

## 4. Eval and Invoke

The `Eval` and `Invoke` families provide a quick and easy way to call small C helpers:

```c
f32 N(calc_initial_vel)(f32 startY, f32 endY, f32 gravity, f32 duration) {
    return (endY - startY + (0.5f * gravity * SQ(duration))) / duration;
}

EvalF(LVar0, N(calc_initial_vel), LVar1, LVar2, LVar3, LVar4)
```

These commands unwrap EVT arguments and store return values automatically. They are useful for moving complex calculations into typed C functions, writing small predicates for `If` statements, or calling simple immediate engine functions. They do not replace `Call` for EVT API functions.

These helpers cannot receive `Evt*`, use `isInitialCall`, or block. A helper must use only `s32`/`b32` arguments or only `f32` arguments, with up to six arguments. Its signature and argument count are checked at compile time.

### Example: Return Values

`Eval` calls an integer helper and stores its `s32` return value:

```c
s32 N(ClampCost)(s32 cost) {
    return MAX(cost, 0);
}

Eval(LVar0, N(ClampCost), LVar1)
```

`EvalF` calls a float helper and stores its `f32` return value:

```c
f32 N(SpringOffset)(f32 curX, f32 targetX) {
    return (targetX - curX) / 10.0f;
}

EvalF(LVar2, N(SpringOffset), LVar0, Float(20.0))
```

### Example: Quick Calls to C

`Invoke` calls a `void` helper with integer arguments:

```c
void N(TakeKentCoins)(void) {
    gPlayerData.coins -= 100;
}

Invoke(N(TakeKentCoins))
```

`InvokeF` does the same for float arguments:

```c
void N(SetSomeOffset)(f32 x, f32 y, f32 z) {
    SomeState.pos.x = x;
    SomeState.pos.y = y;
    SomeState.pos.z = z;
}

InvokeF(N(SetSomeOffset), EVT_AS_VEC3(LVar0))
```

### Example: Branch on Predicate

`IfEval` and `IfNotEval` call a `b32` integer helper:

```c
b32 N(PlayerHasKentMoney)(void) {
    return gPlayerData.coins >= 100;
}

IfNotEval(N(PlayerHasKentMoney))
    Goto("NotEnoughCoins")
EndIf
```

`IfEvalF` and `IfNotEvalF` call a `b32` float helper:

```c
b32 N(WithinRange)(f32 value, f32 min, f32 max) {
    return (min <= value) && (value <= max);
}

IfEvalF(N(WithinRange), LVar0, Float(0.25), Float(12.5))
    BreakLoop
EndIf
```

### Supported Signatures

Each helper family supports exactly typed signatures with zero through six arguments. These are not C varargs; the number of EVT arguments selects a matching function pointer type. Examples:

```c
s32  func(void);                       // Eval with 0 helper args
s32  func(s32 a, s32 b);               // Eval with 2 helper args
f32  func(f32 a, f32 b, f32 c);        // EvalF with 3 helper args
void func(s32 a);                      // Invoke with 1 helper arg
void func(f32 a, f32 b);               // InvokeF with 2 helper args
b32  func(s32 a);                      // IfEval / IfNotEval
b32  func(f32 a, f32 b, f32 c, f32 d); // IfEvalF / IfNotEvalF
```

The function pointer type is checked at compile time. The check is intentionally strict: a helper must use either integer or float arguments, not a mixture of both. Mixed signatures and pointer arguments are rejected. As a second check, the validator ensures that the function operand points to a function.

### When to Use Call

These commands are optional and are not intended to replace `Call`. Keep using `Call` when the helper function:

- needs `Evt* script` to access script variables
- can block, yield, or run over multiple frames
- writes multiple output variables
- uses mixed argument types such as `s32 npcID, f32 x, f32 y, f32 z`
- is already a clear public EVT API like `GetPlayerPos`, `SetNpcPos`, or `TranslateModel`

`Eval` is best used for small calculations, `IfEval` for small decisions, and `Invoke` for immediate, non-blocking actions.

## 5. Vector Helpers

These macros already existed in DX, but become more useful alongside `Eval` and `Invoke`. Many scripts store positions in adjacent LVars:

```c
LVar0 = x
LVar1 = y
LVar2 = z
```

Vector helpers make those variables easier to pass and update together. They do not introduce a new variable type; they are only shorthand for adjacent LVars.

### Passing Vectors

`EVT_AS_VEC2(base)` expands to `base, base + 1`, while `EVT_AS_VEC3(base)` expands to `base, base + 1, base + 2`. This makes it possible to pass consecutive LVars together:

```c
Call(GetPlayerPos, EVT_AS_VEC3(LVar0))
Call(SetNpcPos, NPC_SELF, EVT_AS_VEC3(LVar0))
IfEvalF(N(IsNear), EVT_AS_VEC3(LVar0), EVT_AS_VEC3(LVar3))
    ...
EndIf
```

Component macros select one element from a vector-shaped group of LVars:

```c
AddF(EVT_VEC_Y(LVar0), Float(10.0))
```

### Setting and Manipulating Vectors

Vectors starting at a given base component can be set and modified with a single pseudo-command:

```c
EVT_VEC3F_SET(LVar0, Float(10.0), Float(20.0), Float(30.0))
EVT_VEC3F_ADD(LVar0, Float(0.0), Float(5.0), Float(0.0))
EVT_VEC3F_SUB(LVar0, Float(1.0), Float(0.0), Float(1.0))
```

The macro name describes the dimension (`2` or `3`), value type (`I` or `F`), and operation (`SET`, `ADD`, or `SUB`). Prefix the operation with `V` for vector-to-vector operations:

```c
EVT_VEC3F_VSET(LVar0, LVar3) // LVar0..2 = LVar3..5
EVT_VEC3F_VADD(LVar0, LVar3) // LVar0..2 += LVar3..5
```

## 6. Named Labels

`Label` and `Goto` can now use strings:

```c
Label("WaitForPlayer")
    Wait(1)
    IfNotEval(N(PlayerReady))
        Goto("WaitForPlayer")
    EndIf
```

Vanilla integer labels are still supported. Raw-pointer `Goto` has been removed; use `Jump` when a script genuinely needs to transfer to another entry point.

Labels are now local to the `Thread` scope in which they appear. A `Goto` inside a `Thread` cannot jump to a label outside it, and a `Goto` outside cannot jump in.

The validator understands these scoping rules and will prevent misuse. It also catches duplicate labels in the same scope, `Goto` with no matching `Label`, and too many labels.

## 7. Stricter Case Groups

Case groups are stricter to prevent ambiguous or unsupported control flow. Groups formed with `CaseOrEq` or `CaseAndEq` must be closed with `EndCaseGroup`:

```c
Switch(LVar0)
    CaseOrEq(ITEM_MUSHROOM)
    CaseOrEq(ITEM_SUPER_SHROOM)
    CaseOrEq(ITEM_ULTRA_SHROOM)
        Set(LVar1, true)
    EndCaseGroup
    CaseDefault
        Set(LVar1, false)
EndSwitch
```

The validator rejects missing `EndCaseGroup`, `EndCaseGroup` without an active group, and accidental mixing of `CaseOrEq` with `CaseAndEq` in the same group.

## 8. If Ranges

`IfRange` and `IfNotRange` provide direct inclusive range checks without nested comparisons or a small predicate helper:

```c
IfRange(LVar0, 0, 100)
    Call(InRange)
EndIf

IfNotRange(LVar1, Float(-5.0), Float(5.0))
    Call(OutOfRange)
EndIf
```

`IfRange(VALUE, MIN, MAX)` is true when `MIN <= VALUE <= MAX`.
`IfNotRange(VALUE, MIN, MAX)` is true when `VALUE < MIN` or `VALUE > MAX`.

Like other comparison commands, these compare the raw integer values returned by `evt_get_variable`. Integer ranges should use integer bounds, and fixed-point float ranges should use `Float(...)` bounds. The validator rejects obvious mixed literal bounds:

```c
IfRange(LVar0, 0, Float(100.0)) // rejected
```

Variable bounds are allowed because the validator does not know whether a given variable holds an int or float value at runtime.

## 9. Loop Control

### ContinueLoop

`ContinueLoop` skips the rest of the current loop body and starts the next iteration. It is the loop-control counterpart to `BreakLoop`:

```c
Loop(0)
    Call(PollThing, LVar0)
    IfEq(LVar0, 0)
        ContinueLoop
    EndIf

    Call(HandleReadyThing)
EndLoop
```

For counted loops, `ContinueLoop` still runs the normal `EndLoop` counter handling. It does not bypass decrementing or exiting the loop.

### RetryLoop

`RetryLoop` restarts the current loop iteration without updating its counter. For example, some actor idle scripts use a `Label` anchored at the start of a loop body and `Goto` to pause the loop while an actor is immobilized, without consuming the loop iteration count:

```c
Loop(80)
    Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
            Wait(1)
            Goto(2)
        EndIf
    Wait(1)
EndLoop
```

`RetryLoop` expresses the same behavior without jumping around the loop counter:

```c
Loop(80)
    Call(GetStatusFlags, ACTOR_SELF, LVar1)
    IfFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
        Wait(1)
        RetryLoop
    EndIf
    Wait(1)
EndLoop
```

Using `ContinueLoop` here would still decrement the loop counter, allowing this part of the 80-frame idle to expire while the actor is still immobilized. `RetryLoop` preserves the interrupted iteration. It restarts immediately, so either a `Wait` or a blocking `Call` is required to prevent immediate infinite looping.

## 10. Lerp Loops

`Lerp` turns the common `MakeLerp` / `UpdateLerp` / `Loop` pattern into a first-class block:

```c
Lerp(LVarAngle, 0, 80, 20, EASING_COS_IN_OUT)
    Call(RotateModel, MODEL_o236, LVarAngle, 0, -1, 0)
EndLerp
```

The command sets the output variable before each iteration. The body runs once for elapsed frame `0`, then once per frame until the final elapsed frame has also run. `EndLerp` yields for one frame between iterations, so no `Wait(1)` is needed inside the loop.

This replaces the older boilerplate:

```c
Call(MakeLerp, 0, 80, 20, EASING_COS_IN_OUT)
Loop(0)
    Call(UpdateLerp)
    Call(RotateModel, MODEL_o236, LVar0, 0, -1, 0)
    IfEq(LVar1, false)
        BreakLoop
    EndIf
    Wait(1)
EndLoop
```

`Lerp(VAR, START, END, DURATION, EASING)` accepts integer or `Float(...)` start/end bounds:

```c
Lerp(LVarScale, Float(0.5), Float(1.0), 8, EASING_QUADRATIC_OUT)
    Call(SetModelScale, MODEL_o236, LVarScale, LVarScale, LVarScale)
EndLerp
```

`BreakLoop` exits a lerp early:

```c
Lerp(LVarAlpha, 0, 255, 30, EASING_LINEAR)
    IfEq(MF_CancelFade, true)
        BreakLoop
    EndIf
    Call(SetModelCustomGfx, MODEL_o236, CUSTOM_GFX_0, LVarAlpha)
EndLerp
```

`ContinueLoop` and `RetryLoop` are not allowed inside a `Lerp` block. If a lerp body needs to skip work for a frame, put that work behind an `If` instead.

`Lerp` state is stored in the Evt struct rather than in the script's local variables, so the command only writes its declared output variable. As in the vanilla implementation, only one lerp may be active in a script at a time; nested `Lerp` blocks are rejected by the validator.

The legacy `MakeLerp` and `UpdateLerp` pair reserves `LVar0`, `LVar1`, and `LVarB` through `LVarF`. Only `LVar2` through `LVarA` are untouched by that machinery. These commands remain available for existing scripts, but new scripts should prefer `Lerp` unless they specifically need the legacy local-variable convention.

## 11. Finally Blocks

Scripts often perform setup that must be undone before they exit. Previously, every early exit needed to repeat that cleanup or jump to a shared label. `Finally` provides one cleanup block which runs whether the script ends normally or is killed by another script.

```c
EvtScript N(EVS_UseTempState) = {
    Call(AcquireResource)

    IfEq(GF_SomeCondition, false)
        Return // automatically call ReleaseResource via Finally
    EndIf

    Call(DoSomethingElse)
    Wait(1)

    Finally
        Call(ReleaseResource)
    End
};
```

Here, `ReleaseResource` runs if the script reaches `End`, exits early through `Return`, or is killed externally.

`Finally` belongs at the end of its script scope, immediately before that scope's usual terminator. There is no separate `EndFinally` command:

- use `Finally ... End` for a root script
- use `Finally ... EndThread` for a `Thread`
- use `Finally ... EndChildThread` for a `ChildThread`

### Cleanup Order

Finalizers run as part of termination; they do not wait for a later frame. If a script has an `ExecWait` child or `ChildThread` descendants, those children finish their own finalizers before the parent begins its finalizer.

Scripts started with `Exec`, `ExecGetID`, or `Thread` are detached. They are not children for cleanup purposes and continue running when the script which started them ends.

### Restrictions

A finalizer must complete immediately. This keeps cleanup predictable and ensures that a terminated script does not remain half-alive while waiting for future updates.

- `Finally` must be at the top level of its script, `Thread`, or `ChildThread` scope
- each scope may have only one `Finally` block
- `Call` is allowed only when the API function completes immediately; returning `ApiStatus_BLOCK` causes an assertion
- `KillScript` is allowed, including when its target is already terminating
- `Exec` and `ExecGetID` may start detached scripts
- commands which wait, jump out of the block, or start owned children are not allowed

The validator rejects commands such as `Wait`, `ExecWait`, `Goto`, `Jump`, `BreakLoop`, `ContinueLoop`, `RetryLoop`, `Thread`, `ChildThread`, and `BreakPoint` inside a finalizer. The runtime also asserts if a `Call` tries to start an owned child.

### NPC_SELF and ACTOR_SELF

An Enemy's registered init, interact, AI, hit, auxiliary, and defeat scripts keep both the `Enemy` and its backing `Npc` alive until their cleanup is complete. This means `NPC_SELF` remains valid in their finalizers.

An enemy or partner Actor is likewise kept alive while its registered idle, take-turn, handle-event, and handle-phase scripts clean up. This means `ACTOR_SELF` remains valid in their finalizers.

These guarantees also cover owned `ExecWait` and `ChildThread` descendants of the registered script. They do not cover detached `Exec`, `ExecGetID`, or `Thread` scripts. A detached script inherits the current self-context, but does not keep the corresponding Enemy, Npc, or Actor alive. If a detached companion must not outlive its owner, start it with `ExecGetID` and stop it with `KillScript` from the owner's finalizer.

When all scripts are being shut down together, any detached scripts started by finalizers are shut down too. The hard reset between game states is the intentional exception: it discards the entire script heap without running individual finalizers.

## 12. Awaiting Scripts

`AwaitChildren` waits until all direct `ChildThread` children of the current script have finished. It does not wait for detached `Thread`s, scripts started with `Exec`, or grandchildren of child threads.

```c
ChildThread
    Call(AnimateModelA)
EndChildThread

ChildThread
    Call(AnimateModelB)
EndChildThread

AwaitChildren
Call(ContinueAfterBothAnimations)
```

`AwaitScript(ID)` waits until a script with the given script ID no longer exists. It is useful after `ExecGetID` when a script needs to run independently and the caller still needs a rendezvous point. This is usually accomplished in vanilla EVT with a `Goto` busy loop.

```c
ExecGetID(LVarA, N(EVS_PlayLongEffect))
Call(DoSomethingElse)
AwaitScript(LVarA)
```

## 13. Packed Command Headers

EVT commands now begin with one packed 32-bit header:

```c
opcode: 8 bits
argc:   8 bits
line:  16 bits
```

This is mostly invisible to script authors, but it significantly reduces compiled bytecode size and leaves more VRAM available in each overlay. Because the argument count is now one byte, a command may have at most 255 arguments.

## 14. Buffer Reads

`BufRead` and `FBufRead` are now variadic. The old numbered forms are still available as aliased macros:

```c
BufRead1(LVar0)
BufRead2(LVar0, LVar1)
BufRead3(LVar0, LVar1, LVar2)
BufRead4(LVar0, LVar1, LVar2, LVar3)
```

But new scripts should use the unnumbered forms instead:

```c
UseBuf(Ref(N(SomeData)))
BufRead(LVar0, LVar1, LVar2, LVar3, LVar4, LVar5)

UseFBuf(Ref(N(SomeFloatData)))
FBufRead(LVar0, LVar1, LVar2)
```

Each destination consumes one value from the current buffer and advances the buffer pointer. The old `BufRead1` through `BufRead4` and `FBufRead1` through `FBufRead4` are no longer special. In practice, the number of available LVars limits how many values a script can use at once. Read them in whatever chunks are convenient.

## 15. Command Renames

Several command names were updated to match current engine terminology. In particular, commands which operate on ordinary EvtScripts no longer call them threads, and `BindPadlock` is renamed for the item prompt it actually creates.

| Old name | New name |
| --- | --- |
| `ExecGetTID` | `ExecGetID` |
| `KillThread` | `KillScript` |
| `SuspendThread` | `SuspendScript` |
| `ResumeThread` | `ResumeScript` |
| `IsThreadRunning` | `IsScriptRunning` |
| `BindPadlock` | `BindItemPrompt` |

Compatibility aliases are provided, so the old names still compile. New scripts should prefer the new names.

## Additional Ideas

This EVT Plus proposal covers many new features; here are some that didn't make the cut:

- `Loop(X)` --> `Loop` and `LoopFor(X)`
  - Make infinite loops explicit
- Ownership rework: owner1/owner2 --> ownerKind + owner union
  - Only one owner for a script, less confusion around ID vs pointer for Actor/NPC/Enemy
- `AwaitAll`
  - More expansive than `AwaitChildren`, also waits for detached `Exec` and `Thread`
  - No need to save result from `ExecGetID`, just `Exec` and then `AwaitAll` later
- Make `Unbind` operate for bound Actor and Enemy scripts in addition to Trigger
- Address frailty around `EVT_ENTITY_INDEX`

Perhaps these can be made available in the future.
