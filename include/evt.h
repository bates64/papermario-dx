#pragma once

#include "ultra64.h"

// Should be at least the width of a pointer i.e. intptr_t
typedef s32 Bytecode;
typedef Bytecode EvtVar; /// encoded EVT variable reference

#define EVT_MAX_EVAL_ARGS 6

// pack the opcode, argc, and source line number into a single word for denser bytecode
#define EVT_CMD_HEADER(opcode, argc, line) \
    ((Bytecode)(((((u32)(opcode)) & 0xFF) << 24) | ((((u32)(argc)) & 0xFF) << 16) | (((u32)(line)) & 0xFFFF)))
#define EVT_CMD_OPCODE(raw) (((u32)(raw) >> 24) & 0xFF)
#define EVT_CMD_ARGC(raw)   (((u32)(raw) >> 16) & 0xFF)
#define EVT_CMD_LINE(raw)   ((u32)(raw) & 0xFFFF)

/// helper for calculating command arg counts
#define EVT_CMD_COUNT(argv...) (sizeof((Bytecode[]){argv}) / sizeof(Bytecode))

/// expands to a packed header of the given opcode and arguments with argc calculated automatically
#define EVT_CMD(opcode, argv...) \
    EVT_CMD_HEADER((opcode), EVT_CMD_COUNT(argv), __LINE__), \
    ##argv

enum {
    EVT_OP_INTERNAL_FETCH,
    EVT_OP_END,
    EVT_OP_RETURN,
    EVT_OP_LABEL, ///< Args: label identifier
    EVT_OP_GOTO, ///< Args: label identifier
    EVT_OP_LOOP, ///< Args: number of repeats (0 = infinite)
    EVT_OP_END_LOOP,
    EVT_OP_BREAK_LOOP,
    EVT_OP_CONTINUE_LOOP,
    EVT_OP_RETRY_LOOP,
    EVT_OP_WAIT_FRAMES,
    EVT_OP_WAIT_SECS,
    EVT_OP_IF_EQ, ///< Args: a, b
    EVT_OP_IF_NE, ///< Args: a, b
    EVT_OP_IF_LT, ///< Args: a, b
    EVT_OP_IF_GT, ///< Args: a, b
    EVT_OP_IF_LE, ///< Args: a, b
    EVT_OP_IF_GE, ///< Args: a, b
    EVT_OP_IF_RANGE, ///< Args: value, min, max
    EVT_OP_IF_NOT_RANGE, ///< Args: value, min, max
    EVT_OP_IF_FLAG, ///< Args: a, b
    EVT_OP_IF_NOT_FLAG, ///< Args: a, b
    EVT_OP_ELSE,
    EVT_OP_END_IF,
    EVT_OP_SWITCH, ///< Args: expression to test against
    EVT_OP_SWITCH_CONST, ///< Args: value to test against
    EVT_OP_CASE_EQ, ///< Args: expression to test for
    EVT_OP_CASE_NE, ///< Args: expression to test for
    EVT_OP_CASE_LT, ///< Args: expression to test for
    EVT_OP_CASE_GT, ///< Args: expression to test for
    EVT_OP_CASE_LE, ///< Args: expression to test for
    EVT_OP_CASE_GE, ///< Args: expression to test for
    EVT_OP_CASE_DEFAULT,
    EVT_OP_CASE_OR_EQ, ///< Args: expression to test for
    EVT_OP_CASE_AND_EQ, ///< Args: expression to test for
    EVT_OP_CASE_FLAG, ///< Args: expression to test for
    EVT_OP_END_CASE_GROUP, ///< Ends the case block of EVT_OP_CASE_OR_EQ condition(s).
    EVT_OP_CASE_RANGE, ///< Args: from, to
    EVT_OP_BREAK_SWITCH,
    EVT_OP_END_SWITCH,
    EVT_OP_SET, ///< Args: container, expression
    EVT_OP_SET_CONST, ///< Args: container, value
    EVT_OP_SETF, ///< Args: container, expression
    EVT_OP_ADD, ///< Args: container, increment expression | expression, expression, ...
    EVT_OP_SUB, ///< Args: container, decrement expression | expression, expression
    EVT_OP_MUL, ///< Args: container, multiply expression | expression, expression, ...
    EVT_OP_DIV, ///< Integer division. Args: container, divisor expression | dividend expression, divisor expression
    EVT_OP_MOD, ///< Args: container, divisor expression | dividend expression, divisor expression
    EVT_OP_ADDF, ///< Args: container, increment expression | expression, expression, ...
    EVT_OP_SUBF, ///< Args: container, decrement expression | expression, expression
    EVT_OP_MULF, ///< Args: container, multiply expression | expression, expression, ...
    EVT_OP_DIVF, ///< Args: container, divisor expression | dividend expression, divisor expression
    EVT_OP_NEG, ///< Args: container | container, expression
    EVT_OP_NEGF, ///< Args: container | container, expression
    EVT_OP_ABS, ///< Args: container | container, expression
    EVT_OP_ABSF, ///< Args: container | container, expression
    EVT_OP_SIGN, ///< Args: container | container, expression
    EVT_OP_SIGNF, ///< Args: container | container, expression
    EVT_OP_MIN, ///< Args: container, expression | expression, expression, ...
    EVT_OP_MINF, ///< Args: container, expression | expression, expression, ...
    EVT_OP_MAX, ///< Args: container, expression | expression, expression, ...
    EVT_OP_MAXF, ///< Args: container, expression | expression, expression, ...
    EVT_OP_CLAMP, ///< Args: container, min, max | container, expression, min, max
    EVT_OP_CLAMPF, ///< Args: container, min, max | container, expression, min, max
    EVT_OP_USE_BUF, ///< Args: s32*
    EVT_OP_BUF_READ, ///< Args: container, ...
    EVT_OP_BUF_PEEK, ///< Args: container, index
    EVT_OP_USE_FBUF, ///< Identical to USE_BUFFER. Args: fixed-point s32*
    EVT_OP_FBUF_READ, ///< Args: container, ...
    EVT_OP_FBUF_PEEK, ///< Args: container, index
    EVT_OP_MEM_GET, ///< Args: memory type, container, base address, index
    EVT_OP_MEM_SET, ///< Args: memory type, base address, index, value
    EVT_OP_USE_ARRAY, ///< Args: *s32
    EVT_OP_USE_FLAGS, ///< Args: *s32
    EVT_OP_MALLOC_ARRAY, ///< Allocates a new array. Args: length, s32*
    EVT_OP_BITWISE_AND, ///< Args: container, expression to bitwise AND with
    EVT_OP_BITWISE_AND_CONST, ///< Args: container, value to bitwise AND with
    EVT_OP_BITWISE_OR, ///< Args: container, expression to bitwise OR with
    EVT_OP_BITWISE_OR_CONST, ///< Args: container, value to bitwise OR with
    EVT_OP_CALL, ///< Args: *function, ...
    EVT_OP_EXEC, ///< Args: EvtScript*, ...
    EVT_OP_EXEC_GET_ID, ///< Args: EvtScript*, container, ...
    EVT_OP_EXEC_WAIT, ///< Spawns a script and waits for it to return before continuing. Args: EvtScript*, ...
    EVT_OP_BIND_TRIGGER, ///< Args: EvtScript*, trigger flags, s32 target, has interact prompt, Trigger* out
    EVT_OP_UNBIND, ///< Unbinds any triggers bound to this script.
    EVT_OP_KILL_SCRIPT, ///< Args: ScriptID
    EVT_OP_JUMP, ///< Args: EvtScript*
    EVT_OP_SET_PRIORITY, ///< Args: priority
    EVT_OP_SET_TIMESCALE, ///< Args: timescale
    EVT_OP_SET_GROUP, ///< Args: group
    EVT_OP_BIND_ITEM_PROMPT, ///< Args: EvtScript*, trigger flags, s32 target, ItemList*, tattle msg, has interact prompt
    EVT_OP_SUSPEND_GROUP, ///< Args: group
    EVT_OP_RESUME_GROUP, ///< Args: group
    EVT_OP_SUSPEND_OTHERS, ///< Args: group
    EVT_OP_RESUME_OTHERS, ///< Args: group
    EVT_OP_SUSPEND_SCRIPT, ///< Args: ScriptID
    EVT_OP_RESUME_SCRIPT, ///< Args: ScriptID
    EVT_OP_IS_SCRIPT_RUNNING, ///< Args: ScriptID, container
    EVT_OP_THREAD,
    EVT_OP_END_THREAD,
    EVT_OP_CHILD_THREAD, ///< Parallel threads are killed as soon as the parent script returns.
    EVT_OP_END_CHILD_THREAD,
    EVT_OP_AWAIT_CHILDREN,
    EVT_OP_AWAIT_SCRIPT, ///< Args: ScriptID
    EVT_OP_DEBUG_PRINT_VAR, ///< Args: expression
    EVT_OP_DEBUG_BREAKPOINT,
    EVT_OP_EXPECT_ARGS,
    EVT_OP_FINALLY,
    EVT_OP_EVAL, ///< Args: container, *function, ...
    EVT_OP_EVALF, ///< Args: container, *function, ...
    EVT_OP_INVOKE, ///< Args: *function, ...
    EVT_OP_INVOKEF, ///< Args: *function, ...
    EVT_OP_IF_EVAL, ///< Args: *function, ...
    EVT_OP_IF_NOT_EVAL, ///< Args: *function, ...
    EVT_OP_IF_EVALF, ///< Args: *function, ...
    EVT_OP_IF_NOT_EVALF, ///< Args: *function, ...
    EVT_OP_LERP, ///< Args: container, start, end, duration, easing
    EVT_OP_END_LERP,
};

typedef enum EvtMemType {
    EVT_MEM_U8,
    EVT_MEM_S8,
    EVT_MEM_U16,
    EVT_MEM_S16,
    EVT_MEM_U32,
    EVT_MEM_S32,
    EVT_MEM_F32,
} EvtMemType;

/// the script currently being executed by evt_execute_next_command, or nullptr
extern struct Evt* EvtCurrentScript;

#define MAKE_ENTITY_END      0x80000000

/* Return type of evt_execute_next_command */
#define EVT_CONTINUE 0   /* Continue to next command */
#define EVT_ABORT    1   /* Quit execution */
#define EVT_FINISH   255 /* Return from script */

// EvtScript structural limitations
#define EVT_MAX_NUM_LABELS      16
#define EVT_MAX_LABEL_NAME_LEN  64
#define EVT_MAX_LOOP_DEPTH      8
#define EVT_MAX_SWITCH_DEPTH    8

/// return type of script API functions
typedef s32 ApiStatus;

// normal return values for API_CALLABLE functions
#define ApiStatus_BLOCK  0   /// command is not done; call it again on the next scheduled update
#define ApiStatus_DONE1  1   /// command completed; yield to the scheduler before executing the next command
#define ApiStatus_DONE2  2   /// command completed; advance to next command and continue executing immediately

// descriptive aliases for the legacy DONE1 and DONE2 names
#define ApiStatus_YIELD  ApiStatus_DONE1
#define ApiStatus_NEXT   ApiStatus_DONE2 // or ApiStatus_CONTINUE or stick with ApiStatus_DONE ?

// internal Evt interpreter control values, generally not for user APIs
#define VmStatus_REPEAT  253 /// redispatch immediately; used internally when fetching a command
#define VmStatus_INVALID 254 /// interpreter context was discarded; return without accessing the Evt
#define VmStatus_FINISH  255 /// stop executing without automatically advancing to the next command

enum EventCommandResults {
    EVT_CMD_RESULT_YIELD        = -1,
    EVT_CMD_RESULT_CONTINUE     = 0,
    EVT_CMD_RESULT_ERROR        = 1,
};

enum EvtTerminationState {
    EVT_TERMINATION_NONE                = 0, /// the script is not terminating
    EVT_TERMINATION_AWAITING_CHILDREN   = 1, /// waiting for its children to finish terminating
    EVT_TERMINATION_FINALIZING          = 2, /// Finally block is running
    EVT_TERMINATION_DESTROY_PENDING     = 3, /// ready to be destroyed once it is no longer executing
};

// EventGroupFlags determine when scripts are paused and resumed.
// Each flag corresponds to a set of circumstances which may pause scripts independently of the others.
// These group flags are inherited when one script launches another.
enum EventGroupFlags {
    // Each flag represents a distinct condition for suspending or resuming script execution.
    // These flags are named based on the scenarios that trigger suspension.
    EVT_GROUP_FLAG_INTERACT = 0x01, // Suspended during certain scenes, interactions, and NPC dialogue.
    EVT_GROUP_FLAG_MENUS    = 0x02, // Suspended when menus are open, during pause, item pickups, or "got item" scenes.
    EVT_GROUP_FLAG_CAM      = 0x04, // Never suspended; used exclusively with camera shake (ShakeCam) scripts.
    EVT_GROUP_FLAG_UNUSED   = 0x08, // Unused flag; its original purpose is unknown.
    EVT_GROUP_FLAG_BATTLE   = 0x10, // Suspended during battle entry and exit transitions.

    // Combinations of flags used to assign specific behaviors to scripts.
    // These groups are named after their most common script use-cases.
    EVT_GROUP_NEVER_PAUSE   = 0x00, // Never paused; default for map scripts derived from the main script, which always uses this group.
    EVT_GROUP_PASSIVE_NPC   = EVT_GROUP_FLAG_MENUS | EVT_GROUP_FLAG_UNUSED, // 0xA -- Pauses similar to passive NPC scripts.
    EVT_GROUP_HOSTILE_NPC   = EVT_GROUP_FLAG_INTERACT | EVT_GROUP_FLAG_MENUS | EVT_GROUP_FLAG_UNUSED, // 0xB -- Pauses similar to hostile NPC scripts; used for platforms, machinery, etc.
    EVT_GROUP_EXIT_MAP      = EVT_GROUP_FLAG_INTERACT | EVT_GROUP_FLAG_MENUS | EVT_GROUP_FLAG_UNUSED | EVT_GROUP_FLAG_BATTLE, // 0x1B -- Used for exit map scripts.
    EVT_GROUP_SHAKE_CAM     = EVT_GROUP_FLAG_CAM, // Only used by ShakeCam scripts.
    EVT_GROUP_NOT_BATTLE    = 0xFF & ~EVT_GROUP_FLAG_BATTLE, // 0xEF -- Pauses from anything except battles; default for scripts started via start_script, common in many battle scripts.
};

enum EventPriority {
    EVT_PRIORITY_0          = 0x00, // map main script
    EVT_PRIORITY_1          = 0x01,
    EVT_PRIORITY_A          = 0x0A,
    EVT_PRIORITY_14         = 0x14,
};

enum EventStateFlags {
    EVT_FLAG_ACTIVE             = 0x01,
    EVT_FLAG_PAUSED             = 0x02, ///< paused through suspend_group_script / resume_group_script
    EVT_FLAG_BLOCKED_BY_CHILD   = 0x10,
    EVT_FLAG_RUN_IMMEDIATELY    = 0x20, ///< don't wait for next `update_scripts` call
    EVT_FLAG_THREAD             = 0x40,
    EVT_FLAG_SUSPENDED          = 0x80, ///< doesn't affect child
};
