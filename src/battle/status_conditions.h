#pragma once

#include "common.h"
#include "hud_element.h"
#include "enums.h"
#include "effects.h"
#include "qsort.h"

/*

relevant files:
- src/status_icons.c
- src/battle/190B20.c

*/

// Callbacks
typedef struct EffectInstance* (*GetActorEffect)(struct Condition* condition, struct Actor* actor, Vec3f actorPos);
typedef void (*ApplyToActorPart)(struct Condition* condition, struct ActorPart* part);
typedef f32 (*GetScalingFactor)(struct Condition* condition, struct Actor* actor);

/// Actor status conditions / effects.
typedef struct Conditions {
    /// Linked list.
    struct Condition* head;
} Conditions;

typedef struct Condition {
    /// Next item in the linked list. NULL if last.
    struct Condition* next;

    /// Negative means permanent.
    s32 turnsRemaining;

    HudScript* iconBegin;
    HudScript* iconEnd;    // hilariously, there are also looping icons, but they're unused!
    // the start icon just starts looping after it animates in

    /// Callback in \ref appendGfx_npc_actor.
    GetActorEffect getActorEffect;

    /// Callback in \ref appendGfx_npc_actor.
    ApplyToActorPart applyToActorPart;

    /// Callback in \ref appendGfx_npc_actor.
    GetScalingFactor getScalingFactor;

    /// If TRUE, sets \ref ACTOR_PART_FLAG_TRANSPARENT.
    b32 isTransparent; // TODO: can remove in favour of statusKey

    /// If TRUE, acts as KO (knockout).
    b32 isKo; // TODO: can remove in favour of statusKey?

    b32 glow; // TODO: can remove in favour of statusKey?

    /// Sort priority. If matching, turnsRemaining is used instead.
    s32 priority;

    enum StatusKeys statusKey;

    enum ActorPaletteAdjustments palette;

    /// @see TryPlayerLucky
    b32 skipLuckyAnimation; // TODO: is this disabling the animation or disabling lucky altogether?

    /// If TRUE, enemy actors with this condition will skip their turn.
    b32 makesEnemySkipTurn;
} Condition;

#define foreach_condition(conditions, condition) \
    for (Condition* condition = (conditions)->head; condition != NULL; condition = condition->next)

#define has_condition(conditions, condition, predicate) \
    ({ \
        b32 found = FALSE; \
        for (Condition* condition = (conditions)->head; condition != NULL; condition = condition->next) { \
            if (predicate) { \
                found = TRUE; \
                break; \
            } \
        } \
        found; \
    })

Condition* new_condition(s32 turns);
Condition* new_condition_frozen(s32 turns);
Condition* new_condition_shrink(s32 turns);
Condition* new_condition_transparent(s32 turns);
Condition* new_condition_dizzy(s32 turns);
Condition* new_condition_fear(s32 turns);
Condition* new_condition_sleep(s32 turns);
Condition* new_condition_paralyze(s32 turns);
Condition* new_condition_static(s32 turns);
Condition* new_condition_stop(s32 turns);

s32 count_conditions(Conditions* conditions);

/// Sorts such that the condition with the highest priority is first. If the priorities are equal, the condition with the highest turnsRemaining is first.
void sort_conditions(Conditions* conditions);

void add_condition(Conditions* conditions, Condition* condition);
