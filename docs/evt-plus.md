# EVT Plus

This branch adds quality-of-life features and capabilities to EVT scripts to make them more robust and readable. The goal is to make correct, concise EvtScripts easier to write by providing first-class support for patterns that previously required substantial boilerplate or Goto-based control flow.

The primary features are:

- an optional compile-time EvtScript validator
- argument passing from Exec to child scripts through `ArgVar`
- expanded arithmetic expressions, e.g., `A = B + C + D`, `A = B / C`, `A = min(B, C)`, or `A = clamp(B, MIN, MAX)`
- quick in-line functional interface for C helpers `Eval`, `EvalF`, `Invoke`, `InvokeF`, `IfEval`, and `IfEvalF`
- range conditions with `IfRange` and `IfNotRange`
- `ContinueLoop` as a counterpart to `BreakLoop`
- first-class lerp loops with `Lerp` and `EndLerp`
- cleanup blocks with `Finally` which are guaranteed to run by a terminating script
- await commands for child-threads and single scripts by ID
- new purpose for vector convenience macros using adjacent EVT variables
- variadic buffer reads with `BufRead` and `FBufRead`
- clearer command names with compatibility aliases
- smaller bytecode via packing opcode, argc, and linenum into command header

## Contents

- [Preview](#preview)
- [EvtScript Validation](#1-evtscript-validation)
- [Exec with Arguments](#2-exec-with-arguments)
  - [Literal by Default](#literal-by-default)
  - [ArgVars are Read-Only](#argvars-are-read-only)
  - [ArgVars are Not Passed to Grandchildren](#argvars-are-not-passed-to-grandchildren)
- [Variadic Arithmetic](#3-variadic-arithmetic)
  - [Add and AddF](#add-and-addf)
  - [Mul and MulF](#mul-and-mulf)
  - [Sub, Div, and Mod](#sub-div-and-mod)
  - [Neg, Abs, and Sign](#neg-abs-and-sign)
  - [Min, Max, and Clamp](#min-max-and-clamp)
- [Eval and Invoke](#4-eval-and-invoke)
  - [Example: Return Values](#example-return-values)
  - [Example: Quick Calls to C](#example-quick-calls-to-c)
  - [Example: Branch on Predicate](#example-branch-on-predicate)
  - [Supported Signatures](#supported-signatures)
  - [When to Use Call](#when-to-use-call)
- [Reintroducing Vector Helpers](#5-reintroducing-vector-helpers)
  - [Accessing-as-Vector](#accessing-as-vector)
  - [Setting and Manipulating Vectors](#setting-and-manipulating-vectors)
- [Named Labels](#6-named-labels)
- [Stricter Case Groups](#7-stricter-case-groups)
- [If Ranges](#8-if-ranges)
- [Continue Loop](#9-continue-loop)
- [Lerp Loops](#10-lerp-loops)
- [Finally Blocks](#11-finally-blocks)
- [Awaiting Scripts](#12-awaiting-scripts)
- [Packed Command Headers](#13-packed-command-headers)
- [Buffer Reads](#14-buffer-reads)
- [Command Renames](#15-command-renames)

## Preview

Vanilla EVT needs a temporary local variable just to express a simple calculation:

```c
Set(LVar0, GF_KKJ19_AddedSugar)
Add(LVar0, GF_KKJ19_AddedEgg)
Add(LVar0, GF_KKJ19_AddedNothingWrong)
```

With variadic arithmetic, that can become:

```c
Add(LVar0, GF_KKJ19_AddedSugar, GF_KKJ19_AddedEgg, GF_KKJ19_AddedNothingWrong)
```

Vanilla EVT also needs many tiny `API_CALLABLE` wrappers whose only job is to read arguments, do a calculation, write one LVar, and return:

```c
API_CALLABLE(N(PullVine_UpdatePosition)) {
    Bytecode* args = script->ptrReadPos;
    f32 x1 = evt_get_float_variable(script, *args++);
    f32 x2 = evt_get_float_variable(script, *args++);

    evt_set_float_variable(script, *args++, (x2 - x1) / 10.0f);
    return ApiStatus_DONE2;
}

Call(N(PullVine_UpdatePosition), LVar0, Float(-15.0), LVar2)
```

With `EvalF`, the helper can be a normal typed C function, with cleaner and consistent position for the return value var and named type parameters:

```c
static f32 N(PullVine_UpdatePosition)(f32 cur, f32 target) {
    return (target - cur) / 10.0f;
}

EvalF(LVar2, N(PullVine_UpdatePosition), LVar0, Float(-15.0))
```

For boolean helpers, `IfEval` and `IfEvalF` remove the throwaway output LVar:

```c
static b32 N(IsWithinVineTrigger)(
    f32 playerX, f32 playerY, f32 playerZ,
    f32 vineX, f32 vineY, f32 vineZ
) {
    f32 dx = playerX - vineX;
    f32 dy = playerY - vineY;
    f32 dz = playerZ - vineZ;

    return SQ(dx) + SQ(dy) + SQ(dz) < SQ(60.0f);
}

Call(GetPlayerPos, EVT_AS_VEC3(LVar0))
IfNotEvalF(N(IsWithinVineTrigger), EVT_AS_VEC3(LVar0), EVT_AS_VEC3(LVar3))
    Wait(1)
    Goto("WaitForPlayer")
EndIf
```

## 1. EvtScript Validation

A compile-time structural validator for EvtScripts has been added in `tools/build/evt_validate_obj.py`. This can be disabled completely, or individual scripts can opt-out by *not* following the naming convention `EVS_*`.

The validator catches problems that would crash or cause undefined behavior, as well as unhygienic syntax which was technically valid but unintentional:

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
- `ContinueLoop` outside loops, or inside a lerp loop
- `BreakSwitch` or `Case` outside switches
- unclosed `Thread` or `ChildThread` blocks
- duplicate labels
- label counts beyond runtime limits
- `Goto` with no matching label
- invalid string label references
- invalid `Exec` args
- invalid functions for `Eval`/`Invoke`
- mixed integer/Float literal bounds in `IfRange`/`IfNotRange`
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

Interpreter and script-lifecycle behavior also has a host-side runtime test compiled with sanitizers. The command first runs the whole-project `validate_evt_us` target, then executes test scripts covering ordinary VM behavior and termination:

```sh
python3 tools/test/evt_runtime.py
```

## 2. Exec with Arguments

`Exec`, `ExecGetID`, and `ExecWait` can now pass arguments to the child script. The child reads them through `ArgVar(index)` or the shorthand names `ArgVar0` through `ArgVar7`. Since the storage for them is dynamically allocated, any number of arguments (that is, up to ~250 literals) may be passed and accessed through `ArgVar(index)`.

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

`ExpectArgs(NUM_ARGS)` is a runtime assertion which documents the expected arg count and loudly catches accidental mismatches.

### Literal by Default

Arguments could be passed as either int-var, float-var, or constant. The vanilla pattern is to use `Set`/`SetF`/`SetConst` to handle these different possibilities without ambiguity. Exec-with-args in this branch resolves this by passing all arguments as literal words by default:

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

When properly wrapped, the child can read this float var like any other:

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

They cannot be made *truly* immutable (a determined and misguided modder can still access them directly in c), but no engine function will ever write to them after they have been passed to the child script.

### ArgVars are Not Passed to Grandchildren

Unlike LVars, the ArgVars of a child script are NOT passed to any of its own children, nor returned in any way to the parent. When combined with their read-only property, this provided a handy way to have guaranteed immutable values for the duration of a script's lifetime.

## 3. Variadic Arithmetic

The arithmetic opcodes still support their original two-argument mutating form, but they also accept expression forms.

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

Note that the first args are destination-only when using these forms and not included in the sum.

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

Quicker in-line calls are now available through the `Eval` and `Invoke`:

```c
static f32 N(calc_initial_vel)(f32 startY, f32 endY, f32 gravity, f32 duration) {
     return (endY - startY + (0.5f * gravity * SQ(duration))) / duration;
}

EvalF(LVar0, N(calc_initial_vel), LVar1, LVar2, LVar3, LVar4)
```

These automatically handle evt variables, unwrapping args and wrapping return values. They can be used to break out complex math expressions to small C helpers, write small predicates for if-statements, or fire off simple immediate engine calls. These do not replace `Call` for full EVT API functions.

Their simplified nature carries limitations: they are appropriate for applications which do not need `Evt*`, do not use `isInitialCall`, cannot block, and involve only `s32`/`b32` or `f32` types. Type and arg count checks are performed at compile-time and up to 6 args are supported.

### Example: Return Values

`Eval` calls an integer helper and stores its `s32` return value:

```c
static s32 N(ClampCost)(s32 cost) {
    return MAX(cost, 0);
}

Eval(LVar0, N(ClampCost), LVar1)
```

`EvalF` calls a float helper and stores its `f32` return value:

```c
static f32 N(SpringOffset)(f32 curX, f32 targetX) {
    return (targetX - curX) / 10.0f;
}

EvalF(LVar2, N(SpringOffset), LVar0, Float(20.0))
```

### Example: Quick Calls to C

`Invoke` calls a `void` helper with integer arguments:

```c
static void N(TakeKentCoins)(void) {
    gPlayerData.coins -= 100;
}

Invoke(N(TakeKentCoins))
```

`InvokeF` does the same for float arguments:

```c
static void N(SetSomeOffset)(f32 x, f32 y, f32 z) {
    SomeState.pos.x = x;
    SomeState.pos.y = y;
    SomeState.pos.z = z;
}

InvokeF(N(SetSomeOffset), EVT_AS_VEC3(LVar0))
```

### Example: Branch on Predicate

`IfEval` and `IfNotEval` call a `b32` integer helper:

```c
static b32 N(PlayerHasKentMoney)(void) {
    return gPlayerData.coins >= 100;
}

IfNotEval(N(PlayerHasKentMoney))
    Goto("NotEnoughCoins")
EndIf
```

`IfEvalF` and `IfNotEvalF` call a `b32` float helper:

```c
static b32 N(WithinRange)(f32 value, f32 min, f32 max) {
    return (min <= value) && (value <= max);
}

IfEvalF(N(WithinRange), LVar0, Float(0.25), Float(12.5))
    BreakLoop
EndIf
```

### Supported Signatures

Each helper family supports exactly-typed signatures with 0 through 6 arguments.
These are not C varargs; the arity in the EVT command selects a matching function pointer type. Examples:

```c
s32  func(void);                       // Eval with 0 helper args
s32  func(s32 a, s32 b);               // Eval with 2 helper args
f32  func(f32 a, f32 b, f32 c);        // EvalF with 3 helper args
void func(s32 a);                      // Invoke with 1 helper arg
void func(f32 a, f32 b);               // InvokeF with 2 helper args
b32  func(s32 a);                      // IfEval / IfNotEval
b32  func(f32 a, f32 b, f32 c, f32 d); // IfEvalF / IfNotEvalF
```

The function pointer type is checked at compile time. The check is intentionally strict: you must choose either integers or floats only. Mixed signatures or pointer arguments will error. As a second level of defense, the validator checks that the function operand points at a function.

### When to Use Call

As previously stated, these new commands are completely optional and are not meant to replace `Call`. Use them to simplify your scripts and increase readability. Keep using `Call` when the helper function:

- needs `Evt* script` to access script variables
- can block, yield, or run over multiple frames
- writes multiple output variables
- uses mixed argument types such as `s32 npcID, f32 x, f32 y, f32 z`
- is already a clear public EVT API like `GetPlayerPos`, `SetNpcPos`, or `TranslateModel`

`Eval` is best used for small calculations, `IfEval` for small decisions, and `Invoke` for immediate, non-blocking actions.

## 5. Reintroducing Vector Helpers

These have been in dx for a long time, but have greater purpose when combined with the new `Eval` and `Invoke` commands. For those who are new to them, many scripts store positions as adjacent LVars:

```c
LVar0 = x
LVar1 = y
LVar2 = z
```

Vector helpers codify this arrangement and facilitate parallel operations on vectors. Nothing structural about the variables has been changed, the macros are merely syntactic sugar for referencing them.

### Accessing-as-Vector

`EVT_AS_VEC2(base)` expands to `base, base + 1`.
`EVT_AS_VEC3(base)` expands to `base, base + 1, base + 2`.
We can use these to pass sets of consecutive LVars together:

```c
Call(GetPlayerPos, EVT_AS_VEC3(LVar0))
Call(SetNpcPos, NPC_SELF, EVT_AS_VEC3(LVar0))
IfEvalF(N(IsNear), EVT_AS_VEC3(LVar0), EVT_AS_VEC3(LVar3))
    ...
EndIf
```

Component macros are available for extracting a single component from a 'vector':

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

There are integer and float versions for both 2D and 3D vectors:

- `EVT_VEC2I_SET`, `EVT_VEC2F_SET`, `EVT_VEC3I_SET`, `EVT_VEC3F_SET`;
- `EVT_VEC2I_ADD`, `EVT_VEC2F_ADD`, `EVT_VEC3I_ADD`, `EVT_VEC3F_ADD`;
- `EVT_VEC2I_SUB`, `EVT_VEC2F_SUB`, `EVT_VEC3I_SUB`, `EVT_VEC3F_SUB`;
- `EVT_VEC2I_VSET`, `EVT_VEC2F_VSET`, `EVT_VEC3I_VSET`, `EVT_VEC3F_VSET`;
- `EVT_VEC2I_VADD`, `EVT_VEC2F_VADD`, `EVT_VEC3I_VADD`, `EVT_VEC3F_VADD`;
- `EVT_VEC2I_VSUB`, `EVT_VEC2F_VSUB`, `EVT_VEC3I_VSUB`, `EVT_VEC3F_VSUB`.

The `V` forms are vector-to-vector:

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

Vanilla integer-style labels are still supported, but raw pointer `Goto` support has been removed. Use the `Jump` command for those (or rather, don't use them at all).

The VM has also been modified to make Labels local to the `Thread` scope in which they live: `Goto` statements within a `Thread` can no longer jump to labels outside, nor can `Goto` outside jump in. This was unintended behavior before.

The validator understands these scoping rules and will prevent misuse. It also catches duplicate labels in the same scope, `Goto` with no matching `Label`, and too many labels.

## 7. Stricter Case Groups

Case groups have become stricter to prevent unintended and undefined use-cases. `CaseOrEq` and `CaseAndEq` represent explicit fallthrough groups and must be closed with `EndCaseGroup`:

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

`IfRange` and `IfNotRange` allow direct inclusive range, without having to nest comparisons or using a small predicate helper:

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

## 9. Continue Loop

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

`ContinueLoop` is not allowed inside a `Lerp` block. If a lerp body needs to skip work for a frame, put that work behind an `If` instead.

`Lerp` state is managed by the VM, no longer store in local variables (as in vanilla), so it does not collide with scripts that use local variables for other work. Just like the vanilla implementation, only one `Lerp` may be active in a script at a time; nested `Lerp` blocks are rejected by the validator. `MakeLerp` and `UpdateLerp` remain available for existing scripts, but new scripts should prefer `Lerp` unless they need the old explicit `LVar0`/`LVar1` behavior.

## 11. Finally Blocks

`Finally` marks a cleanup tail for a script. When present, the cleanup tail runs immediately before the script is destroyed by `Return`, normal `End`/`EndThread`/`EndChildThread`, or an external `kill_script`.

Any blocking child or `ChildThread` descendants are finalized first. The parent cleanup tail then runs after its children have released their resources and copied back any blocking-child state. Termination does not yield to a later frame: reentrant cleanup is deferred only as far as the nearest safe interpreter boundary in the same VM invocation.

The whole cleanup tail must finish right away. It cannot wait for another frame, block on an API call, or start an owned child. `Exec` and `ExecGetID` may launch detached scripts which continue independently after the finalizing script is destroyed.

This is intended for temporary resources or state that must be released even if the script exits early:

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

The finalizer is anchored to the normal script terminator. There is no `EndFinally`; use `Finally ... End` for root scripts, `Finally ... EndThread` for threads, and `Finally ... EndChildThread` for child threads.

Finalizers are deliberately restricted:

- `Finally` must be top-level in its script, `Thread`, or `ChildThread` scope
- only one `Finally` is allowed per scope
- finalizers run immediately and must not block or yield to a later frame
- obvious blocking or control-flow commands such as `Wait`, `ExecWait`, `Goto`, `Jump`, `BreakLoop`, `ContinueLoop`, `Thread`, `ChildThread`, and `BreakPoint` are rejected by the validator
- `Call` is allowed, but the runtime will assert if the function returns `ApiStatus_BLOCK` or starts an owned child

Detached scripts started during an individual finalizer survive that script's termination. `kill_all_scripts` continues scanning until no running scripts remain, so detached scripts launched by finalizers do not escape a global shutdown.

`KillScript` is allowed and is useful for cleaning up a detached companion started earlier with `ExecGetID`. Killing an already-terminating script, including the current script from its own finalizer, is an idempotent no-op. A target normally finishes before `KillScript` returns; when reentrant ownership requires unwinding an active child or command first, cleanup still completes later in the same VM invocation.

`clear_script_list` remains the intentional exception: it is part of the hard memory reset between game states and bypasses per-script cleanup along with the rest of the old heap.

This makes `Finally` suitable for cleanup work like freeing resources, restoring flags, unregistering transient state, or undoing setup performed earlier in the script.

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
ExecGetID(N(EVS_PlayLongEffect), LVarA)
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

This is mostly invisible to modders, but it significantly reduces the final compiled version of each script, opening up more room in vram per overlay. Now that argc is a single byte, command argument counts are limited to 255.

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

Each destination consumes one value from the current buffer and advances the buffer pointer. The old `BufRead1` through `BufRead4` and `FBufRead1` through `FBufRead4` are no longer special. The true cap is the number of `LocalVar`s available to store values in. Read in whatever chunks are convenient.

## 15. Command Renames

Several command names were adjusted from very old conventions to align better with current understanding of the engine and avoid confusion among related concepts. Specifically `BindPadlock` and references to `Thread` which actually apply to normal EvtScripts and not in-line `Thread` blocks.

| Old name | New name | Reason |
| --- | --- | --- |
| `ExecGetTID` | `ExecGetID` | The returned value is a script ID, unrelated to `Thread`. |
| `KillThread` | `KillScript` | The runtime kills scripts by script ID. |
| `SuspendThread` | `SuspendScript` | Suspends scripts by script ID. |
| `ResumeThread` | `ResumeScript` | Resumes scripts by script ID. |
| `IsThreadRunning` | `IsScriptRunning` | The check asks whether a script ID still exists. |
| `BindPadlock` | `BindItemPrompt` | The command binds a generic item prompt, not just padlocks. |

Compatibility aliases are provided, so the old names still compile. New scripts should prefer the new names.
