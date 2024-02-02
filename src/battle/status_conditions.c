#include "status_conditions.h"

// Default callbacks

void apply_to_actor_part_default(struct Condition* condition, struct ActorPart* part) {
    // Do nothing
}

struct EffectInstance* get_actor_effect_default(struct Condition* condition, struct Actor* actor, Vec3f actorPos) {
    return NULL;
}

f32 get_scaling_factor_default(struct Condition condition, struct Actor* actor) {
    return 1.0f;
}

Condition* new_condition(s32 turns) {
    Condition* condition = heap_malloc(sizeof(*condition));
    condition->iconBegin = NULL;
    condition->iconEnd = NULL;
    condition->turnsRemaining = turns;
    condition->applyToActorPart = apply_to_actor_part_default;
    condition->getActorEffect = get_actor_effect_default;
    condition->getScalingFactor = get_scaling_factor_default;
    condition->isTransparent = FALSE;
    condition->isKo = FALSE;
    condition->glow = FALSE;
    condition->priority = 0;
    condition->statusKey = STATUS_END;
    condition->palette = ACTOR_PAL_ADJUST_NONE;
    condition->skipLuckyAnimation = FALSE;
    return NULL;
}

s32 count_conditions(Conditions* conditions) {
    s32 count = 0;
    foreach_condition(conditions, condition) {
        count++;
    }
    return count;
}

/// Sorts such that the condition with the highest priority is first. If the priorities are equal, the condition with the highest turnsRemaining is first.
void sort_conditions(Conditions* conditions) {
    Condition tmp;
    #define LESS(i, j) \
        (conditions->head[i].priority > conditions->head[j].priority || \
        (conditions->head[i].priority == conditions->head[j].priority && conditions->head[i].turnsRemaining > conditions->head[j].turnsRemaining))
    #define SWAP(i, j) \
        tmp = conditions->head[i], \
        conditions->head[i] = conditions->head[j], \
        conditions->head[j] = tmp
    QSORT(count_conditions(conditions), LESS, SWAP);
    #undef LESS
    #undef SWAP
}

void add_condition(Conditions* conditions, Condition* condition) {
    // TODO: increase the turnsRemaining of an existing condition
    if (has_condition(conditions, c, c->statusKey == condition->statusKey)) {
        return;
    }

    condition->next = conditions->head;
    conditions->head = condition;
    sort_conditions(conditions);
}

// Frozen

struct EffectInstance* get_actor_effect_frozen(struct Condition* condition, struct Actor* actor, Vec3f actorPos) {
    EffectInstance* effect = actor->icePillarEffect;
    if (actor->icePillarEffect != NULL) {
        if ((gBattleStatus.flags1 & BS_FLAGS1_SHOW_PLAYER_DECORATIONS) ||
            (!(gBattleStatus.flags1 & BS_FLAGS1_TATTLE_OPEN) && (actor->flags & ACTOR_FLAG_SHOW_STATUS_ICONS)))
        {
            effect->data.icePillar->pos.x = actorPos.x;
            effect->data.icePillar->pos.y = actorPos.y;
            effect->data.icePillar->pos.z = actorPos.z;
            effect->data.icePillar->scale = actor->size.y / 24.0;
        } else {
            effect->data.icePillar->pos.x = NPC_DISPOSE_POS_X;
            effect->data.icePillar->pos.y = NPC_DISPOSE_POS_Y;
            effect->data.icePillar->pos.z = NPC_DISPOSE_POS_Z;
        }
    }
    return effect;
}

Condition* new_condition_frozen(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->getActorEffect = get_actor_effect_frozen;
    condition->statusKey = STATUS_KEY_FROZEN;
    condition->priority = 1;
    condition->skipLuckyAnimation = TRUE;
    return condition;
}

// Shrink

f32 get_scaling_factor_shrink(struct Condition condition, struct Actor* actor) {
    return 0.4f;
}

Condition* new_condition_shrink(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->getActorEffect = get_scaling_factor_shrink;
    condition->statusKey = STATUS_KEY_SHRINK;
    return condition;
}

// Transparent

Condition* new_condition_transparent(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->isTransparent = TRUE;
    condition->statusKey = STATUS_KEY_TRANSPARENT;
    return condition;
}

// Dizzy

Condition* new_condition_dizzy(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->statusKey = STATUS_KEY_DIZZY;
    condition->skipLuckyAnimation = TRUE;
    return condition;
}

// Fear

Condition* new_condition_fear(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->statusKey = STATUS_KEY_FEAR;
    condition->skipLuckyAnimation = TRUE;
    return condition;
}

// Sleep

Condition* new_condition_sleep(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->statusKey = STATUS_KEY_SLEEP;
    condition->skipLuckyAnimation = TRUE;
    return condition;
}

// Paralyze

Condition* new_condition_paralyze(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->statusKey = STATUS_KEY_PARALYZE;
    condition->skipLuckyAnimation = TRUE;
    return condition;
}

// Static

Condition* new_condition_static(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->statusKey = STATUS_KEY_STATIC;
    return condition;
}

// Stop

Condition* new_condition_stop(s32 turns) {
    Condition* condition = new_condition(turns);
    condition->statusKey = STATUS_KEY_STOP;
    condition->skipLuckyAnimation = TRUE;
    return condition;
}
