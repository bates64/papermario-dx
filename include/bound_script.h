#pragma once

#include "common.h"

// finds the live script currently recorded by this binding
static ALWAYS_INLINE Evt* get_bound_script(BoundScript* boundScript) {
    if (boundScript->live == nullptr) {
        return nullptr;
    }

    return get_script_by_id(boundScript->liveID);
}

// records a newly started script in this binding
static ALWAYS_INLINE void assign_bound_script(BoundScript* boundScript, Evt* script) {
    boundScript->live = script;
    boundScript->liveID = script->id;
}

// forgets the current instance without changing the script source
static ALWAYS_INLINE void clear_bound_script(BoundScript* boundScript) {
    boundScript->live = nullptr;
    boundScript->liveID = 0;
}

// checks whether the bound script is still running and clears a stale binding
static ALWAYS_INLINE b32 is_bound_script_running(BoundScript* boundScript) {
    if (boundScript->live != nullptr && does_script_exist(boundScript->liveID)) {
        return true;
    }

    boundScript->live = nullptr;
    boundScript->liveID = 0;
    return false;
}

// applies flags to the bound script if it still exists
static ALWAYS_INLINE void set_bound_script_flags(BoundScript* boundScript, s32 flags) {
    Evt* script = get_bound_script(boundScript);

    if (script != nullptr) {
        set_script_flags(script, flags);
    }
}

// removes flags from the bound script if it still exists
static ALWAYS_INLINE void clear_bound_script_flags(BoundScript* boundScript, s32 flags) {
    Evt* script = get_bound_script(boundScript);

    if (script != nullptr) {
        clear_script_flags(script, flags);
    }
}

// suspends the bound script and its children if one is recorded
static ALWAYS_INLINE void suspend_bound_script(BoundScript* boundScript) {
    if (boundScript->live != nullptr) {
        suspend_all_script(boundScript->liveID);
    }
}

// resumes the bound script and its children if one is recorded
static ALWAYS_INLINE void resume_bound_script(BoundScript* boundScript) {
    if (boundScript->live != nullptr) {
        resume_all_script(boundScript->liveID);
    }
}

// kills the bound script without clearing a replacement started by Finally
static ALWAYS_INLINE void kill_bound_script(BoundScript* boundScript) {
    if (boundScript->live != nullptr) {
        s32 liveID = boundScript->liveID;

        kill_script_by_ID(liveID);

        // Finally may have bound a replacement with a new ID
        if (boundScript->liveID == liveID) {
            boundScript->live = nullptr;
            boundScript->liveID = 0;
        }
    }
}
