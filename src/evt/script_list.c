#include "common.h"
#include "bound_script.h"
#include "hud_element.h"
#include "dx/config.h"
#include "dx/debug_menu.h"

s32 UniqueScriptCounter = 1;
s32 IsUpdatingScripts = false;
f32 GlobalTimeRate = 1.0f;

// script_list
BSS u32* gMapFlags;
BSS s32* gMapVars;
BSS s32 gNumScripts;
BSS ScriptList gWorldScriptList;
BSS ScriptList gBattleScriptList;
BSS ScriptList* gCurrentScriptListPtr;
BSS s32 gScriptIndexList[MAX_SCRIPTS];
BSS s32 gScriptIdList[MAX_SCRIPTS];
BSS s32 gScriptListCount;

// evt
BSS char evtDebugPrintBuffer[0x100];

// map_api
BSS struct LavaReset* gLavaResetList;
BSS s32 LastSafeFloor;

// model_api
BSS AnimatedModelList gBattleMeshAnimationList;
BSS AnimatedModelList gWorldMeshAnimationList;
BSS AnimatedModelList* gCurrentMeshAnimationListPtr;

// npc_api
BSS s32 wExtraPartnerID;
BSS s32 wExtraPartnerNpcID;

// msg_api
BSS s32 ShowMessageScreenOffsetX;
BSS s32 ShowMessageScreenOffsetY;
BSS MessagePrintState* gCurrentPrintContext;
BSS MessagePrintState* D_802DB268;
BSS s32 D_802DB264;

// player_api
BSS Npc playerNpcData;
BSS u16 PlayerImgFXFlags;
BSS VirtualEntityList bBattleVirtualEntityList;
BSS VirtualEntityList wWorldVirtualEntityList;
BSS VirtualEntityList* gCurrentVirtualEntityListPtr;

// audio_api
BSS MusicEvent* MusicEventList;
BSS Evt* RunningMusicEvents[10];
BSS s32 RunningMusicEventIDs[10];

// item_api
BSS PopupMenu gItemChoicePopupMenu;

// why is this at the end? com section vs bss?
BSS u32 gWorldMapFlags[MAX_MAPFLAGS];
BSS u32 gBattleMapFlags[MAX_MAPFLAGS];

BSS u32 gWorldMapVars[MAX_MAPVARS];
BSS u32 gBattleMapVars[MAX_MAPVARS];

BSS PushBlockGrid* wPushBlockGrids[8];

BSS s32 DoorModelsSwingCW[3];
BSS s32 DoorModelsSwingCCW[3];

s32 evt_execute_next_command(Evt* script);

b32 evt_is_valid_label_value(Bytecode label);
b32 evt_label_values_match(Bytecode lhs, Bytecode rhs);
Bytecode* evt_find_thread_block_end(Bytecode* startLine, s32 endOpcode);
static b32 script_has_children(Evt* script);
static void kill_script_children(Evt* script);

void sort_scripts(void) {
    s32 temp_a0;
    s32 temp_a1;
    s32 tempID;
    Evt* curScript;
    ScriptList** currentScriptListPtr;
    s32 i;
    s32 j;
    s32 x;
    s32 numValidScripts = 0;
    s32* scriptIndexList = gScriptIndexList;
    s32* scriptIdList = gScriptIdList;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        curScript = (*gCurrentScriptListPtr)[i];
        if (curScript != nullptr) {
            if (curScript->stateFlags != 0) {
                scriptIndexList[numValidScripts] = i;
                scriptIdList[numValidScripts] = curScript->id;
                numValidScripts++;
            }
        }
    }

    gScriptListCount = numValidScripts;
    for (i = 0; i < (x = numValidScripts - 1); i++) {
        scriptIndexList = gScriptIndexList;
        currentScriptListPtr = &gCurrentScriptListPtr;
        scriptIdList = gScriptIdList;
        for (j = i + 1; j < numValidScripts; j++) {
            temp_a1 = scriptIndexList[i];
            temp_a0 = scriptIndexList[j];
            x = i;
            if ((**currentScriptListPtr)[temp_a1]->priority > (**currentScriptListPtr)[temp_a0]->priority) {
                scriptIndexList[i] = temp_a0;
                scriptIndexList[j] = temp_a1;
                tempID = scriptIdList[i];
                scriptIdList[i] = scriptIdList[j];
                scriptIdList[j] = tempID;
            }
        }
    }
}

void scan_script_structure(Evt* script) {
    Bytecode* curLine = script->ptrNextLine;
    s32 labelCount = 0;
    b32 inFinally = false;
    s32 endOpcode;
    s32 i;

    if (script->threadParent != nullptr) {
        endOpcode = EVT_OP_END_CHILD_THREAD;
    } else if (script->stateFlags & EVT_FLAG_THREAD) {
        endOpcode = EVT_OP_END_THREAD;
    } else {
        endOpcode = EVT_OP_END;
    }

    script->ptrFinally = nullptr;

    for (i = 0; i < ARRAY_COUNT(script->labelValuePtrs); i++) {
        script->labelValuePtrs[i] = nullptr;
    }

    while (true) {
        s32 rawCmd = *curLine++;
        s32 opcode = EVT_CMD_OPCODE(rawCmd);
        s32 numArgs = EVT_CMD_ARGC(rawCmd);
        Bytecode* args = curLine;

        curLine += numArgs;

        if (opcode == endOpcode) {
            return;
        }
        if (opcode == EVT_OP_END) {
            PANIC_MSG("Unexpected End while scanning labels for opcode 0x%lX", (u32) endOpcode);
        }

        switch (opcode) {
            case EVT_OP_THREAD:
                curLine = evt_find_thread_block_end(curLine, EVT_OP_END_THREAD);
                break;
            case EVT_OP_CHILD_THREAD:
                curLine = evt_find_thread_block_end(curLine, EVT_OP_END_CHILD_THREAD);
                break;
            case EVT_OP_FINALLY:
                ASSERT_MSG(!inFinally, "Script contains multiple Finally commands");
                script->ptrFinally = curLine;
                inFinally = true;
                break;
            case EVT_OP_LABEL: {
                Bytecode label = *args;

                ASSERT_MSG(!inFinally, "Label commands are not allowed inside Finally");
                ASSERT_MSG(evt_is_valid_label_value(label), "Invalid Label value: 0x%08lX", (u32) label);
                ASSERT(labelCount < ARRAY_COUNT(script->labelValuePtrs));

                for (i = 0; i < labelCount; i++) {
                    ASSERT_MSG(!evt_label_values_match(label, *script->labelValuePtrs[i]), "Duplicate Label value: 0x%08lX", (u32) label);
                }

                script->labelValuePtrs[labelCount++] = args;
                break;
            }
        }
    }
}

void clear_script_list(void) {
    s32 i;

    EvtCurrentScript = nullptr;

    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        gCurrentScriptListPtr = &gWorldScriptList;
        gMapVars = gWorldMapVars;
        gMapFlags = gWorldMapFlags;
    } else {
        gCurrentScriptListPtr = &gBattleScriptList;
        gMapVars = gBattleMapVars;
        gMapFlags = gBattleMapFlags;
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        (*gCurrentScriptListPtr)[i] = nullptr;
    }

    gNumScripts = 0;
    gScriptListCount = 0;
    IsUpdatingScripts = false;

    for (i = 0; i < MAX_MAPVARS; i++) {
        gMapVars[i] = 0;
    }

    for (i = 0; i < MAX_MAPFLAGS; i++) {
        gMapFlags[i] = 0;
    }

    #if DX_DEBUG_MENU
    dx_debug_evt_reset();
    #endif

    clear_virtual_entity_list();
    reset_model_animators();
}

void init_script_list(void) {
    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        gCurrentScriptListPtr = &gWorldScriptList;
        gMapVars = gWorldMapVars;
        gMapFlags = gWorldMapFlags;
    } else {
        gCurrentScriptListPtr = &gBattleScriptList;
        gMapVars = gBattleMapVars;
        gMapFlags = gBattleMapFlags;
    }

    gNumScripts = 0;
    IsUpdatingScripts = false;

    init_virtual_entity_list();
    init_model_animators();
}

// enforces current gTimeFreezeMode on newly created script
void suspend_frozen_scripts(Evt* script) {
    switch (gTimeFreezeMode) {
        default:
        case TIME_FREEZE_NONE:
        case TIME_FREEZE_EXIT:
            return;
        case TIME_FREEZE_PARTIAL:
            suspend_all_group(EVT_GROUP_FLAG_INTERACT);
            return;
        case TIME_FREEZE_FULL:
        case TIME_FREEZE_POPUP_MENU:
            suspend_all_group(EVT_GROUP_FLAG_MENUS);
            return;
    }
}

Evt* start_script(EvtScript* source, s32 priority, s32 flags) {
    Evt* newScript;
    s32 scriptListCount;
    s32 curScriptIndex;
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        if ((*gCurrentScriptListPtr)[i] == nullptr) {
            break;
        }
    }

    ASSERT(i < MAX_SCRIPTS);
    curScriptIndex = i;

    (*gCurrentScriptListPtr)[curScriptIndex] = newScript = heap_malloc(sizeof(*newScript));
    gNumScripts++;
    ASSERT(newScript != nullptr);

    newScript->stateFlags = flags | EVT_FLAG_ACTIVE;
    newScript->curOpcode = EVT_OP_INTERNAL_FETCH;
    newScript->priority = priority;
    newScript->id = UniqueScriptCounter++;
    newScript->ptrNextLine = (Bytecode*)source;
    newScript->ptrFirstLine = (Bytecode*)source;
    newScript->ptrCurLine = (Bytecode*)source;
    newScript->userData = nullptr;
    newScript->argVars = nullptr;
    newScript->argCount = 0;
    newScript->lerpActive = false;
    newScript->blockingParent = nullptr;
    newScript->blockingChild = nullptr;
    newScript->threadParent = nullptr;
    newScript->owner1.actorID = -1;
    newScript->owner2.npcID = -1;
    newScript->loopDepth = -1;
    newScript->switchDepth = -1;
    newScript->groupFlags = EVT_GROUP_NOT_BATTLE;
    newScript->frameCounter = 0.0f;
    newScript->timeScale = GlobalTimeRate;
    newScript->debugPaused = false;
    newScript->terminationState = EVT_TERMINATION_NONE;
    newScript->isExecuting = false;
    newScript->isTerminatingChildren = false;

    scriptListCount = 0;

    for (i = 0; i < ARRAY_COUNT(newScript->varTable); i++) {
        newScript->varTable[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(newScript->varFlags); i++) {
        newScript->varFlags[i] = 0;
    }

    scan_script_structure(newScript);

    if (IsUpdatingScripts && (newScript->stateFlags & EVT_FLAG_RUN_IMMEDIATELY)) {
        scriptListCount = gScriptListCount++;
        gScriptIndexList[scriptListCount] = curScriptIndex;
        gScriptIdList[scriptListCount] = newScript->id;
    }

    suspend_frozen_scripts(newScript);

    if (UniqueScriptCounter == 0) {
        UniqueScriptCounter = 1;
    }

    return newScript;
}

Evt* start_script_in_group(EvtScript* source, u8 priority, u8 flags, u8 groupFlags) {
    Evt* newScript;
    s32 scriptListCount;
    s32 curScriptIndex;
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        if ((*gCurrentScriptListPtr)[i] == nullptr) {
            break;
        }
    }

    ASSERT(i < MAX_SCRIPTS);
    curScriptIndex = i;

    (*gCurrentScriptListPtr)[curScriptIndex] = newScript = heap_malloc(sizeof(*newScript));
    gNumScripts++;
    ASSERT(newScript != nullptr);

    newScript->stateFlags = flags | EVT_FLAG_ACTIVE;
    newScript->curOpcode = EVT_OP_INTERNAL_FETCH;
    newScript->priority = priority;
    newScript->id = UniqueScriptCounter++;
    newScript->ptrNextLine = (Bytecode*)source;
    newScript->ptrFirstLine = (Bytecode*)source;
    newScript->ptrCurLine = (Bytecode*)source;
    newScript->userData = nullptr;
    newScript->argVars = nullptr;
    newScript->argCount = 0;
    newScript->lerpActive = false;
    newScript->blockingParent = nullptr;
    newScript->blockingChild = nullptr;
    newScript->threadParent = nullptr;
    newScript->owner1.actorID = -1;
    newScript->owner2.npcID = -1;
    newScript->loopDepth = -1;
    newScript->switchDepth = -1;
    newScript->groupFlags = groupFlags;
    newScript->frameCounter = 0.0f;
    newScript->timeScale = GlobalTimeRate;
    newScript->debugPaused = false;
    newScript->terminationState = EVT_TERMINATION_NONE;
    newScript->isExecuting = false;
    newScript->isTerminatingChildren = false;

    scriptListCount = 0;

    for (i = 0; i < ARRAY_COUNT(newScript->varTable); i++) {
        newScript->varTable[i] = 0;
    }
    for (i = 0; i < ARRAY_COUNT(newScript->varFlags); i++) {
        newScript->varFlags[i] = 0;
    }

    scan_script_structure(newScript);

    if (IsUpdatingScripts && (newScript->stateFlags & EVT_FLAG_RUN_IMMEDIATELY)) {
        scriptListCount = gScriptListCount++;
        gScriptIndexList[scriptListCount] = curScriptIndex;
        gScriptIdList[scriptListCount] = newScript->id;
    }

    suspend_frozen_scripts(newScript);

    if (UniqueScriptCounter == 0) {
        UniqueScriptCounter = 1;
    }

    return newScript;
}

Evt* start_child_script(Evt* parentScript, EvtScript* source, s32 flags) {
    s32 curScriptIndex;
    s32 scriptListCount;
    Evt* child;
    s32 i;

    ASSERT_MSG(
        EvtCurrentScript == nullptr || EvtCurrentScript->terminationState != EVT_TERMINATION_FINALIZING,
        "Finally block attempted to start an owned child script"
    );
    ASSERT_MSG(parentScript->terminationState == EVT_TERMINATION_NONE, "Cannot add a child to a terminating script");

    for (i = 0; i < MAX_SCRIPTS; i++) {
        if ((*gCurrentScriptListPtr)[i] == nullptr) {
            break;
        }
    }

    ASSERT(i < MAX_SCRIPTS);
    curScriptIndex = i;

    (*gCurrentScriptListPtr)[curScriptIndex] = child = heap_malloc(sizeof(*child));
    gNumScripts++;
    ASSERT(child != nullptr);

    parentScript->blockingChild = child;
    parentScript->stateFlags |= EVT_FLAG_BLOCKED_BY_CHILD;
    child->stateFlags = flags | EVT_FLAG_ACTIVE;
    child->ptrCurLine = child->ptrFirstLine = child->ptrNextLine = (Bytecode*)source;

    child->curOpcode = EVT_OP_INTERNAL_FETCH;
    child->userData = nullptr;
    child->argVars = nullptr;
    child->argCount = 0;
    child->lerpActive = false;
    child->blockingParent = parentScript;
    child->blockingChild = nullptr;
    child->threadParent = nullptr;
    child->priority = parentScript->priority + 1;
    child->id = UniqueScriptCounter++;
    child->owner1 = parentScript->owner1;
    child->owner2 = parentScript->owner2;
    child->loopDepth = -1;
    child->switchDepth = -1;
    child->groupFlags = parentScript->groupFlags;
    child->array = parentScript->array;
    child->flagArray = parentScript->flagArray;
    child->timeScale = GlobalTimeRate;
    child->frameCounter = 0.0f;
    child->debugPaused = false;
    child->terminationState = EVT_TERMINATION_NONE;
    child->isExecuting = false;
    child->isTerminatingChildren = false;

    scriptListCount = 0;

    for (i = 0; i < ARRAY_COUNT(child->varTable); i++) {
        child->varTable[i] = parentScript->varTable[i];
    }

    for (i = 0; i < ARRAY_COUNT(child->varFlags); i++) {
        child->varFlags[i] = parentScript->varFlags[i];
    }

    scan_script_structure(child);
    if (IsUpdatingScripts) {
        scriptListCount = gScriptListCount++;
        gScriptIndexList[scriptListCount] = curScriptIndex;
        gScriptIdList[scriptListCount] = child->id;
    }

    suspend_frozen_scripts(child);

    if (UniqueScriptCounter == 0) {
        UniqueScriptCounter = 1;
    }

    return child;
}

Evt* start_child_thread(Evt* parentScript, Bytecode* nextLine, s32 newState) {
    Evt* child;
    s32 curScriptIndex;
    s32 i;
    s32 scriptListCount;

    ASSERT_MSG(
        EvtCurrentScript == nullptr || EvtCurrentScript->terminationState != EVT_TERMINATION_FINALIZING,
        "Finally block attempted to start an owned child script"
    );
    ASSERT_MSG(parentScript->terminationState == EVT_TERMINATION_NONE, "Cannot add a child to a terminating script");

    for (i = 0; i < MAX_SCRIPTS; i++) {
        if ((*gCurrentScriptListPtr)[i] == nullptr) {
            break;
        }
    }

    ASSERT(i < MAX_SCRIPTS);
    curScriptIndex = i;

    (*gCurrentScriptListPtr)[curScriptIndex] = child = heap_malloc(sizeof(*child));
    gNumScripts++;
    ASSERT(child != nullptr);

    child->stateFlags = newState | EVT_FLAG_ACTIVE;
    child->ptrNextLine = nextLine;
    child->ptrFirstLine = nextLine;
    child->ptrCurLine = nextLine;
    child->curOpcode = EVT_OP_INTERNAL_FETCH;
    child->userData = nullptr;
    child->argVars = nullptr;
    child->argCount = 0;
    child->lerpActive = false;
    child->blockingParent = nullptr;
    child->threadParent = parentScript;
    child->blockingChild = nullptr;
    child->priority = parentScript->priority;
    child->id = UniqueScriptCounter++;
    child->owner1.actorID = parentScript->owner1.actorID;
    child->owner2.npcID = parentScript->owner2.npcID;
    child->loopDepth = -1;
    child->switchDepth = -1;
    child->groupFlags = parentScript->groupFlags;
    child->array = parentScript->array;
    child->flagArray = parentScript->flagArray;
    child->timeScale = GlobalTimeRate;
    child->frameCounter = 0.0f;
    child->debugPaused = false;
    child->terminationState = EVT_TERMINATION_NONE;
    child->isExecuting = false;
    child->isTerminatingChildren = false;

    scriptListCount = 0;

    for (i = 0; i < ARRAY_COUNT(child->varTable); i++) {
        child->varTable[i] = parentScript->varTable[i];
    }

    for (i = 0; i < ARRAY_COUNT(child->varFlags); i++) {
        child->varFlags[i] = parentScript->varFlags[i];
    }

    scan_script_structure(child);
    if (IsUpdatingScripts) {
        scriptListCount = gScriptListCount++;
        gScriptIndexList[scriptListCount] = curScriptIndex;
        gScriptIdList[scriptListCount] = child->id;
    }

    if (UniqueScriptCounter == 0) {
        UniqueScriptCounter = 1;
    }

    suspend_frozen_scripts(child);
    return child;
}

// points an existing script at new source while keeping its local state
Evt* replace_script(Evt* script, Bytecode* source, s32 flags) {
    ASSERT(script->terminationState == EVT_TERMINATION_NONE);
    ASSERT_MSG(
        script->blockingParent == nullptr && script->threadParent == nullptr,
        "Cannot detach and reset an owned child script"
    );

    // keep a child's Finally block from destroying this script while it is being reset
    ASSERT(!script->isTerminatingChildren);
    script->isTerminatingChildren = true;
    kill_script_children(script);
    script->isTerminatingChildren = false;
    ASSERT_MSG(!script_has_children(script), "Cannot reset a script beneath an active child command");
    ASSERT_MSG(
        script->terminationState == EVT_TERMINATION_NONE,
        "Child cleanup attempted to terminate a script while it was being reset"
    );

    script->ptrNextLine = source;
    script->ptrFirstLine = source;
    script->ptrCurLine = source;
    script->curOpcode = EVT_OP_INTERNAL_FETCH;
    script->frameCounter = 0;
    script->stateFlags |= flags;
    script->timeScale = 1.0f;

    #if DX_DEBUG_MENU
    dx_debug_evt_force_detach(script);
    #endif

    if (script->userData != nullptr) {
        heap_free(script->userData);
        script->userData = nullptr;
    }

    if (script->argVars != nullptr) {
        heap_free(script->argVars);
        script->argVars = nullptr;
        script->argCount = 0;
    }
    script->lerpActive = false;

    script->loopDepth = -1;
    script->switchDepth = -1;
    script->blockingParent = nullptr;
    script->threadParent = nullptr;
    script->blockingChild = nullptr;
    script->frameCounter = 0.0f;
    script->timeScale = GlobalTimeRate;
    scan_script_structure(script);
    suspend_frozen_scripts(script);

    return script;
}

// restarts a script from its original source while keeping its local state
Evt* restart_script(Evt* script) {
    Bytecode* ptrFirstLine = script->ptrFirstLine;

    ASSERT(script->terminationState == EVT_TERMINATION_NONE);

    script->loopDepth = -1;
    script->switchDepth = -1;
    script->lerpActive = false;
    script->curOpcode = EVT_OP_INTERNAL_FETCH;

    script->ptrNextLine = ptrFirstLine;
    script->ptrCurLine = ptrFirstLine;
    script->timeScale = 1.0f;
    script->frameCounter = 0;

    script->timeScale = GlobalTimeRate;

    scan_script_structure(script);
    suspend_frozen_scripts(script);

    return script;
}

void update_scripts(void) {
    s32 i;

    if (gGameStatusPtr->debugScripts == DEBUG_SCRIPTS_NO_UPDATE) {
        return;
    }

    IsUpdatingScripts = true;
    sort_scripts();

    // iterate over all scripts, executing commands in each until EVT_CMD_RESULT_YIELD
    for (i = 0; i < gScriptListCount; i++) {
        Evt* script = (*gCurrentScriptListPtr)[gScriptIndexList[i]];

        if (script != nullptr
            && script->id == gScriptIdList[i]
            && script->stateFlags != 0
            && script->terminationState == EVT_TERMINATION_NONE
            && !(script->stateFlags & (EVT_FLAG_SUSPENDED | EVT_FLAG_BLOCKED_BY_CHILD | EVT_FLAG_PAUSED))
        ) {
            b32 stop = false;
            s32 status;

            script->frameCounter += script->timeScale;

            do {
                if (script->frameCounter < 1.0) {
                    // Continue to next script
                    break;
                };

                script->frameCounter -= 1.0;
                status = evt_execute_next_command(script);
                if (status == EVT_CMD_RESULT_ERROR) {
                    stop = true;
                    break;
                }
            } while (status != EVT_CMD_RESULT_YIELD);

            if (stop) {
                break;
            }
        }
    }
    IsUpdatingScripts = false;
    EvtCurrentScript = nullptr;
}

// checks whether an address and ID still identify the same live script
static b32 script_ref_matches(Evt* script, s32 scriptID) {
    s32 i;

    if (script == nullptr) {
        return false;
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate == script) {
            return candidate->id == scriptID;
        }
    }
    return false;
}

// checks whether a script still has an ExecWait child or any ChildThread scripts
static b32 script_has_children(Evt* script) {
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

// terminates every child owned by this script
static void kill_script_children(Evt* script) {
    Evt* blockingChild = script->blockingChild;
    s32 i;

    if (blockingChild != nullptr && blockingChild->terminationState == EVT_TERMINATION_NONE) {
        kill_script(blockingChild);
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate != nullptr
            && candidate->threadParent == script
            && candidate->terminationState == EVT_TERMINATION_NONE
        ) {
            kill_script(candidate);
        }
    }
}

static void evt_destroy_script(Evt* script);

/*
 * terminating a script has four steps:
 *
 * 1. request termination of its children
 * 2. wait for each child to finish Finally and be destroyed
 * 3. run this script's Finally block
 * 4. destroy the script once the interpreter is no longer using it
 *
 * children always finish terminating before their parent. this function continues as far as it
 * can, but may stop while a child or the interpreter is still using the script.
 */
static void evt_continue_termination(Evt* script) {
    ASSERT(script != nullptr);

    // terminate every child before starting this script's Finally block
    if (script->terminationState == EVT_TERMINATION_AWAITING_CHILDREN) {
        if (script->isTerminatingChildren) {
            // a child terminated while this script was already terminating its children
            return;
        }

        script->isTerminatingChildren = true;
        kill_script_children(script);
        if (script_has_children(script)) {
            // at least one child is still executing and will terminate later
            script->isTerminatingChildren = false;
            return;
        }

        if (script->ptrFinally != nullptr) {
            // start at the first command after Finally
            script->ptrNextLine = script->ptrFinally;
            script->curOpcode = EVT_OP_INTERNAL_FETCH;
            script->terminationState = EVT_TERMINATION_FINALIZING;
        } else {
            // without Finally, the script is ready to be destroyed
            script->terminationState = EVT_TERMINATION_DESTROY_PENDING;
        }
        script->isTerminatingChildren = false;
    }

    // do not run Finally or destroy a script while the interpreter is using it
    if (script->isExecuting) {
        return;
    }

    if (script->terminationState == EVT_TERMINATION_FINALIZING) {
        Evt* previousScript = EvtCurrentScript;
        s32 previousScriptID = 0;
        s32 scriptID = script->id;
        s32 status;

        // since Finally runs immediately, we must remember which script the interpreter was using before
        if (previousScript != nullptr) {
            previousScriptID = previousScript->id;
        }
        status = evt_execute_next_command(script);
        ASSERT_MSG(status != EVT_CMD_RESULT_ERROR, "Finally block failed during script termination");

        // restore the previous script only if that exact script still exists
        if (script_ref_matches(previousScript, previousScriptID)) {
            EvtCurrentScript = previousScript;
        } else {
            EvtCurrentScript = nullptr;
        }

        // Finally may have destroyed this script and reused its address
        if (!script_ref_matches(script, scriptID)) {
            return;
        }
    }

    ASSERT(!script->isExecuting);
    if (script->terminationState == EVT_TERMINATION_DESTROY_PENDING) {
        evt_destroy_script(script);
    }
}

// moves a script to the next step when it is killed or reaches Return, Finally, or End
void evt_terminate_script(Evt* script) {
    ASSERT(script != nullptr);

    switch (script->terminationState) {
        case EVT_TERMINATION_NONE:
            script->terminationState = EVT_TERMINATION_AWAITING_CHILDREN;
            script->blocked = false;

            #if DX_DEBUG_MENU
            script->debugPaused = false;
            script->debugStep = DEBUG_EVT_STEP_NONE;
            #endif
            break;
        case EVT_TERMINATION_FINALIZING:
            // End has finished the Finally block
            ASSERT(!script_has_children(script));
            script->terminationState = EVT_TERMINATION_DESTROY_PENDING;
            break;
        default:
            return;
    }

    evt_continue_termination(script);
}

// requests termination of a known-live script; repeated requests have no effect
void kill_script(Evt* script) {
    if (script != nullptr && script->terminationState == EVT_TERMINATION_NONE) {
        evt_terminate_script(script);
    }
}

// destroys a terminated script and frees the resources it owns
static void evt_destroy_script(Evt* script) {
    Evt* blockingParent = script->blockingParent;
    Evt* threadParent = script->threadParent;
    Evt* parent = blockingParent;
    s32 listIdx, i;

    // cannot have two parents (but could have none)
    ASSERT(blockingParent == nullptr || threadParent == nullptr);

    if (parent == nullptr) {
        parent = threadParent;
    }

    ASSERT(script->terminationState == EVT_TERMINATION_DESTROY_PENDING);
    ASSERT(!script->isExecuting);
    ASSERT(!script_has_children(script));

    for (listIdx = 0; listIdx < MAX_SCRIPTS; listIdx++) {
        if ((*gCurrentScriptListPtr)[listIdx] == script) {
            break;
        }
    }
    ASSERT(listIdx < MAX_SCRIPTS);

    // ExecWait copies the child's local state back and unblocks its parent
    if (blockingParent != nullptr) {
        ASSERT(blockingParent->blockingChild == script);
        blockingParent->blockingChild = nullptr;
        blockingParent->stateFlags &= ~EVT_FLAG_BLOCKED_BY_CHILD;

        for (i = 0; i < ARRAY_COUNT(blockingParent->varTable); i++) {
            blockingParent->varTable[i] = script->varTable[i];
        }

        for (i = 0; i < ARRAY_COUNT(blockingParent->varFlags); i++) {
            blockingParent->varFlags[i] = script->varFlags[i];
        }
    }

    #if DX_DEBUG_MENU
    dx_debug_evt_force_detach(script);
    #endif

    // free resources owned directly by the script
    if (script->userData != nullptr) {
        heap_free(script->userData);
        script->userData = nullptr;
    }

    if (script->argVars != nullptr) {
        heap_free(script->argVars);
        script->argVars = nullptr;
        script->argCount = 0;
    }
    if (EvtCurrentScript == script) {
        EvtCurrentScript = nullptr;
    }
    heap_free((*gCurrentScriptListPtr)[listIdx]);
    (*gCurrentScriptListPtr)[listIdx] = nullptr;
    gNumScripts--;

    // the parent may now be able to run Finally or be destroyed
    if (parent != nullptr) {
        evt_continue_termination(parent);
    }
}

// marks this script as no longer executing, then continues its termination if needed
s32 evt_finish_execution(Evt* script, s32 result) {
    ASSERT(script->isExecuting);
    ASSERT(script->terminationState != EVT_TERMINATION_FINALIZING);

    script->isExecuting = false;

    // continue termination that was waiting for the interpreter to finish
    evt_continue_termination(script);
    return result;
}

void kill_script_by_ID(s32 id) {
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];
        if (candidate != nullptr && candidate->id == id) {
            kill_script(candidate);
        }
    }
}

void kill_all_scripts(void) {
    b32 hasKilled = false;
    s32 scriptsKilled = 0;
    s32 i;

    do {
        hasKilled = false;
        for (i = 0; i < MAX_SCRIPTS; i++) {
            Evt* candidate = (*gCurrentScriptListPtr)[i];
            if (candidate != nullptr && candidate->terminationState == EVT_TERMINATION_NONE) {
                kill_script(candidate);
                hasKilled = true;
                scriptsKilled++;
                ASSERT_MSG(scriptsKilled < 10000, "kill_all_scripts did not settle");
            }
        }
    } while (hasKilled);
}

// checks whether a script with this ID is still alive
s32 does_script_exist(s32 id) {
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate != nullptr && candidate->id == id) {
            return true;
        }
    }
    return false;
}

// checks whether a script has any ChildThread children
s32 does_script_have_child_threads(Evt* script) {
    s32 i;

    if (script == nullptr) {
        return false;
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* candidate = (*gCurrentScriptListPtr)[i];

        if (candidate != nullptr && candidate->threadParent == script) {
            return true;
        }
    }
    return false;
}

void set_script_priority(Evt* script, s32 priority) {
    script->priority = priority;
}

void set_script_timescale(Evt* script, f32 timescale) {
    script->timeScale = timescale * GlobalTimeRate;
}

void set_global_timespace(f32 timeScale) {
    GlobalTimeRate = timeScale;
}

f32 get_global_timespace(void) {
    return GlobalTimeRate;
}

void set_script_group(Evt* script, s32 groupFlags) {
    script->groupFlags = groupFlags;
}

Trigger* bind_trigger(EvtScript* script, s32 flags, s32 triggerFlagIndex, s32 triggerVar0, s32 triggerVar1,
                      s32 priority, s32 arg6) {
    Trigger* trigger;
    TriggerBlueprint bp;

    bp.flags = flags | TRIGGER_SCRIPT_BOUND;
    bp.colliderID = triggerFlagIndex;
    bp.tattleMsg = 0;
    bp.onActivateFunc = evt_trigger_on_activate_exec_script;
    bp.hasPlayerInteractPrompt = arg6;

    trigger = create_trigger(&bp);
    trigger->script.source = script;
    clear_bound_script(&trigger->script);
    trigger->priority = priority;
    trigger->varTable[0] = triggerVar0;
    trigger->varTable[1] = triggerVar1;
    return trigger;
}

Trigger* bind_trigger_1(EvtScript* script, s32 flags, s32 triggerFlagIndex, s32 triggerVar0, s32 triggerVar1,
                        s32 priority) {
    return bind_trigger(script, flags, triggerFlagIndex, triggerVar0, triggerVar1, priority, 1);
}

void suspend_group_script(Evt* script, s32 groupFlags) {
    Evt* childScript = script->blockingChild;
    s32 i;

    if (childScript != nullptr) {
        suspend_group_script(childScript, groupFlags);
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* scriptContextPtr = (*gCurrentScriptListPtr)[i];

        if (scriptContextPtr != nullptr && scriptContextPtr->threadParent == script) {
            suspend_group_script(scriptContextPtr, groupFlags);
        }
    }

    if ((script->groupFlags & groupFlags) != 0) {
        script->stateFlags |= EVT_FLAG_PAUSED;
    }
}

void resume_group_script(Evt* script, s32 groupFlags) {
    Evt* childScript = script->blockingChild;
    s32 i;

    if (childScript != nullptr) {
        resume_group_script(childScript, groupFlags);
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* scriptContextPtr = (*gCurrentScriptListPtr)[i];

        if (scriptContextPtr != nullptr && scriptContextPtr->threadParent == script) {
            suspend_group_script(scriptContextPtr, groupFlags);
        }
    }

    if ((script->groupFlags & groupFlags) != 0) {
        script->stateFlags &= ~EVT_FLAG_PAUSED;
    }
}

void suspend_all_script(s32 id) {
    s32 i;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* scriptContextPtr = (*gCurrentScriptListPtr)[i];

        if (scriptContextPtr != nullptr && scriptContextPtr->id == id) {
            suspend_group_script(scriptContextPtr, EVT_GROUP_NOT_BATTLE);
        }
    }
}

void resume_all_script(s32 id) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr && scriptContextPtr->id == id) {
            resume_group_script(scriptContextPtr, EVT_GROUP_NOT_BATTLE);
        }
    }
}

void suspend_group_script_index(s32 id, s32 groupFlags) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr && scriptContextPtr->id == id) {
            suspend_group_script(scriptContextPtr, groupFlags);
        }
    }
}

void resume_group_script_index(s32 id, s32 groupFlags) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr && scriptContextPtr->id == id) {
            resume_group_script(scriptContextPtr, groupFlags);
        }
    }
}

void suspend_all_group(s32 groupFlags) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr) {
            suspend_group_script(scriptContextPtr, groupFlags);
        }
    }
}

void resume_all_group(s32 groupFlags) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr) {
            resume_group_script(scriptContextPtr, groupFlags);
        }
    }
}

void suspend_group_others(Evt* script, s32 groupFlags) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr && scriptContextPtr != script) {
            suspend_group_script(scriptContextPtr, groupFlags);
        }
    }
}

void resume_group_others(Evt* script, s32 groupFlags) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        scriptContextPtr = (*gCurrentScriptListPtr)[i];
        if (scriptContextPtr != nullptr && scriptContextPtr != script) {
            resume_group_script(scriptContextPtr, groupFlags);
        }
    }
}

Evt* get_script_by_index(s32 index) {
    return (*gCurrentScriptListPtr)[index];
}

Evt* get_script_by_id(s32 id) {
    s32 i;
    Evt* scriptContextPtr;

    for (i = 0; i < MAX_SCRIPTS; i++) {
        if ((*gCurrentScriptListPtr)[i] != nullptr) {
            scriptContextPtr = (*gCurrentScriptListPtr)[i];
            if (scriptContextPtr->id == id) {
                return scriptContextPtr;
            }
        }
    }
    return 0;
}

void set_script_flags(Evt* script, s32 flags) {
    Evt* childScript = script->blockingChild;
    s32 i;

    script->stateFlags |= flags;
    if (childScript != nullptr) {
        set_script_flags(childScript, flags);
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* scriptContextPtr = (*gCurrentScriptListPtr)[i];

        if (scriptContextPtr != nullptr && scriptContextPtr->threadParent == script) {
            set_script_flags(scriptContextPtr, flags);
        }
    }
}

void clear_script_flags(Evt* script, s32 flags) {
    Evt* childScript = script->blockingChild;
    s32 i;

    script->stateFlags &= ~flags;
    if (childScript != nullptr) {
        clear_script_flags(childScript, flags);
    }

    for (i = 0; i < MAX_SCRIPTS; i++) {
        Evt* scriptContextPtr = (*gCurrentScriptListPtr)[i];

        if (scriptContextPtr != nullptr && scriptContextPtr->threadParent == script) {
            clear_script_flags(scriptContextPtr, flags);
        }
    }
}
