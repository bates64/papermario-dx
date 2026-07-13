#include "common.h"
#include "bound_script.h"
#include "npc.h"
#include "effects.h"
#include "world/ai.h"
#include "battle/battle.h"

API_CALLABLE(SetEncounterStatusFlags) {
    Bytecode* args = script->ptrReadPos;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    s32 flagBits = *args++;

    if (evt_get_variable(script, *args++)) {
        currentEncounter->flags |= flagBits;
    } else {
        currentEncounter->flags &= ~flagBits;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(IsStartingConversation) {
    Bytecode* args = script->ptrReadPos;
    s32 outVar = *args++;

    evt_set_variable(script, outVar, is_starting_conversation());
    return ApiStatus_DONE2;
}

API_CALLABLE(LoadDemoBattle) {
    Bytecode* args = script->ptrReadPos;

    load_demo_battle(evt_get_variable(script, *args++));
    return ApiStatus_DONE2;
}

API_CALLABLE(MakeNpcs) {
    Bytecode* args = script->ptrReadPos;
    s32 flags;
    s32* npcList;

    if (isInitialCall) {
        flags = evt_get_variable(script, *args++);
        npcList = (s32*) evt_get_variable(script, *args++);
        make_npcs(flags, gGameStatusPtr->mapID, npcList);
    } else {
        if (gEncounterState != ENCOUNTER_STATE_CREATE) {
            return ApiStatus_DONE2;
        }
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(RemoveNpc) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);

    if ((s32)enemy != NPC_SELF && npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);
    kill_enemy(enemy);
    return ApiStatus_DONE1;
}

API_CALLABLE(RemoveEncounter) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 id = evt_get_variable(script, *args++);

    if ((s32)enemy != NPC_SELF && id == NPC_SELF) {
        id = enemy->npcID;
    }

    enemy = get_enemy(id);
    kill_encounter(enemy);
    return ApiStatus_DONE1;
}

API_CALLABLE(GetBattleOutcome) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gCurrentEncounter.battleOutcome);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetOwnerEncounterTrigger) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, script->owner1.enemy->encountered);
    return ApiStatus_DONE2;
}

API_CALLABLE(DoNpcDefeat) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Evt* newScript;

    kill_script(script);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_DEATH];
    newScript = start_script(&EVS_NpcDefeat, EVT_PRIORITY_A, 0);
    set_bound_script_live(&enemy->scripts.defeat, newScript);
    newScript->owner1.enemy = enemy;
    newScript->owner2.npcID = enemy->npcID;
    newScript->groupFlags = enemy->scriptGroup;

    return ApiStatus_DONE2;
}

void start_battle(Evt* script, s32 songID) {
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Enemy* enemy = script->owner1.enemy;
    Encounter* encounter;
    s32 i;

    resume_all_group(EVT_GROUP_FLAG_INTERACT);

    currentEncounter->hitType = ENCOUNTER_TRIGGER_NONE;
    enemy->encountered = true;
    currentEncounter->curEnemy = enemy;
    currentEncounter->curEncounter = currentEncounter->encounterList[enemy->encounterIndex];
    currentEncounter->firstStrikeType = FIRST_STRIKE_NONE;
    currentEncounter->forbidFleeing = false;
    currentEncounter->songID = songID;
    currentEncounter->unk_18 = -1;

    suspend_bound_script(&enemy->scripts.ai);
    suspend_bound_script(&enemy->scripts.aux);

    disable_player_input();
    partner_disable_input();

    encounter = currentEncounter->curEncounter;
    for (i = 0; i < encounter->count; i++) {
        enemy = encounter->enemy[i];
        if (enemy != nullptr && (!(enemy->flags & ENEMY_FLAG_ENABLE_HIT_SCRIPT) || enemy == currentEncounter->curEnemy)) {
            if (enemy->scripts.hit.source != nullptr) {
                Evt* hitEvtInstance;
                enemy->encountered = true;

                hitEvtInstance = start_script(enemy->scripts.hit.source, EVT_PRIORITY_A, 0);

                set_bound_script_live(&enemy->scripts.hit, hitEvtInstance);
                hitEvtInstance->owner1.enemy = enemy;
                hitEvtInstance->owner2.npcID = enemy->npcID;
                hitEvtInstance->groupFlags = enemy->scriptGroup;
            }
        }
    }

    currentEncounter->fadeOutAmount = 0;
    currentEncounter->substateDelay = 0;
    currentEncounter->scriptedBattle = true;
    gEncounterState = ENCOUNTER_STATE_PRE_BATTLE;
    EncounterStateChanged = true;
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT;
}

API_CALLABLE(StartBattle) {
    start_battle(script, -1);
    return ApiStatus_DONE1;
}

API_CALLABLE(StartBattleWith) {
    Bytecode* args = script->ptrReadPos;

    start_battle(script, evt_get_variable(script, *args++));
    return ApiStatus_DONE1;
}

API_CALLABLE(StartBossBattle) {
    Bytecode* args = script->ptrReadPos;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Enemy* enemy = script->owner1.enemy;
    s32 songID = evt_get_variable(script, *args++);
    Encounter* encounter;
    s32 i;

    resume_all_group(EVT_GROUP_FLAG_INTERACT);

    currentEncounter->hitType = ENCOUNTER_TRIGGER_NONE;
    enemy->encountered = true;
    currentEncounter->curEnemy = enemy;
    currentEncounter->curEncounter = currentEncounter->encounterList[enemy->encounterIndex];
    currentEncounter->firstStrikeType = FIRST_STRIKE_NONE;
    currentEncounter->forbidFleeing = true;
    currentEncounter->songID = songID;
    currentEncounter->unk_18 = -1;

    suspend_bound_script(&enemy->scripts.ai);
    suspend_bound_script(&enemy->scripts.aux);

    disable_player_input();
    partner_disable_input();

    encounter = currentEncounter->curEncounter;
    for (i = 0; i < encounter->count; i++) {
        enemy = encounter->enemy[i];
        if ((enemy != nullptr && (
            !(enemy->flags & ENEMY_FLAG_ENABLE_HIT_SCRIPT) || enemy == currentEncounter->curEnemy)
            ) && enemy->scripts.hit.source != nullptr) {
            enemy->encountered = true;

            script = start_script(enemy->scripts.hit.source, EVT_PRIORITY_A, 0);

            set_bound_script_live(&enemy->scripts.hit, script);

            script->owner1.enemy = enemy;
            script->owner2.npcID = enemy->npcID;
            script->groupFlags = enemy->scriptGroup;
        }
    }

    currentEncounter->fadeOutAmount = 0;
    currentEncounter->substateDelay = 0;
    currentEncounter->scriptedBattle = true;
    gEncounterState = ENCOUNTER_STATE_PRE_BATTLE;
    EncounterStateChanged = true;
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT;

    return ApiStatus_DONE1;
}

API_CALLABLE(SetBattleMusic) {
    Bytecode* args = script->ptrReadPos;
    Bytecode songID = evt_get_variable(script, *args++);
    EncounterStatus* currentEncounter = &gCurrentEncounter;

    currentEncounter->forbidFleeing = true;
    currentEncounter->songID = songID;
    currentEncounter->unk_18 = -1;
    return ApiStatus_DONE2;
}

API_CALLABLE(BindNpcAI) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* newScriptSource = (EvtScript*)evt_get_variable(script, *args++);
    Evt* newScript;
    s32 groupFlags;

    if ((s32)enemy != NPC_SELF && npcID == NPC_SELF) {
        npcID = enemy->npcID;
    } else {
        enemy = get_enemy(npcID);
    }

    if (enemy->flags & ENEMY_FLAG_PASSIVE) {
        groupFlags = EVT_GROUP_PASSIVE_NPC;
    } else {
        groupFlags = EVT_GROUP_HOSTILE_NPC;
    }

    kill_bound_script(&enemy->scripts.ai);
    enemy->scripts.ai.source = newScriptSource;
    newScript = start_script(newScriptSource, EVT_PRIORITY_A, 0);
    set_bound_script_live(&enemy->scripts.ai, newScript);
    newScript->owner1.enemy = enemy;
    newScript->owner2.npcID = npcID;
    newScript->groupFlags = groupFlags;
    return ApiStatus_DONE2;
}

API_CALLABLE(BindNpcIdle) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* aiBytecode = (EvtScript*)evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);
    enemy->scripts.ai.source = aiBytecode;

    return ApiStatus_DONE2;
}

API_CALLABLE(RestartNpcAI) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    Evt* newScript;
    s32 groupFlags;

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    if (enemy->flags & ENEMY_FLAG_PASSIVE) {
        groupFlags = EVT_GROUP_PASSIVE_NPC;
    } else {
        groupFlags = EVT_GROUP_HOSTILE_NPC;
    }

    kill_bound_script(&enemy->scripts.ai);
    newScript = start_script(enemy->scripts.ai.source, EVT_PRIORITY_A, 0);
    set_bound_script_live(&enemy->scripts.ai, newScript);
    newScript->owner1.enemy = enemy;
    newScript->owner2.npcID = npcID;
    newScript->groupFlags = groupFlags;

    return ApiStatus_DONE2;
}

API_CALLABLE(EnableNpcAI) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    b32 enabled = evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    if (enabled) {
        resume_bound_script(&enemy->scripts.ai);
    } else {
        suspend_bound_script(&enemy->scripts.ai);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetNpcAux) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* newScriptSource = (EvtScript*)evt_get_variable(script, *args++);
    Evt* newScript;

    if ((s32)enemy != NPC_SELF && npcID == NPC_SELF) {
        npcID = enemy->npcID;
    } else {
        enemy = get_enemy(npcID);
    }

    kill_bound_script(&enemy->scripts.aux);

    enemy->scripts.aux.source = newScriptSource;
    if (newScriptSource != nullptr) {
        newScript = start_script(newScriptSource, EVT_PRIORITY_A, 0);
        set_bound_script_live(&enemy->scripts.aux, newScript);
        newScript->owner1.enemy = enemy;
        newScript->owner2.npcID = npcID;
        newScript->groupFlags = script->groupFlags;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(BindNpcAux) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* auxBytecode = (EvtScript*)evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);
    enemy->scripts.aux.source = auxBytecode;

    return ApiStatus_DONE2;
}

API_CALLABLE(RestartNpcAux) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    Evt* newScript;
    s32 groupFlags;

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    if (enemy->flags & ENEMY_FLAG_PASSIVE) {
        groupFlags = EVT_GROUP_PASSIVE_NPC;
    } else {
        groupFlags = EVT_GROUP_HOSTILE_NPC;
    }

    kill_bound_script(&enemy->scripts.aux);
    newScript = start_script(enemy->scripts.aux.source, EVT_PRIORITY_A, 0);
    set_bound_script_live(&enemy->scripts.aux, newScript);
    newScript->owner1.enemy = enemy;
    newScript->owner2.npcID = npcID;
    newScript->groupFlags = groupFlags;

    return ApiStatus_DONE2;
}

API_CALLABLE(EnableNpcAux) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    b32 enabled = evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    if (enabled) {
        resume_bound_script(&enemy->scripts.aux);
    } else {
        suspend_bound_script(&enemy->scripts.aux);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(BindNpcInteract) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* interactSource = (EvtScript*)evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    kill_bound_script(&enemy->scripts.interact);
    enemy->scripts.interact.source = interactSource;

    return ApiStatus_DONE2;
}

API_CALLABLE(BindNpcHit) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* hitBytecode = (EvtScript*)evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    kill_bound_script(&enemy->scripts.hit);
    enemy->scripts.hit.source = hitBytecode;

    return ApiStatus_DONE2;
}

API_CALLABLE(BindNpcDefeat) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    EvtScript* defeatBytecode = (EvtScript*)evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);
    enemy->scripts.defeat.source = defeatBytecode;

    return ApiStatus_DONE2;
}

API_CALLABLE(SetSelfVar) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 index = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    enemy->varTable[index] = value;
    return ApiStatus_DONE2;
}

API_CALLABLE(GetSelfVar) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 index = evt_get_variable(script, *args++);
    s32 outVar = *args++;

    evt_set_variable(script, outVar, enemy->varTable[index]);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetNpcVar) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    s32 varIdx = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);
    enemy->varTable[varIdx] = value;

    return ApiStatus_DONE2;
}

API_CALLABLE(GetNpcVar) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    s32 varIdx = evt_get_variable(script, *args++);
    s32 outVar = *args++;

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);
    evt_set_variable(script, outVar, enemy->varTable[varIdx]);

    return ApiStatus_DONE2;
}

API_CALLABLE(SetSelfRotation) {
    Bytecode* args = script->ptrReadPos;
    Npc* self = get_npc_unsafe(script->owner2.npcID);
    s32 rotX = evt_get_variable(script, *args++);
    s32 rotY = evt_get_variable(script, *args++);
    s32 rotZ = evt_get_variable(script, *args++);

    self->rot.x = rotX;
    self->rot.y = rotY;
    self->rot.z = rotZ;

    return ApiStatus_DONE2;
}

API_CALLABLE(SetSelfEnemyFlags) {
    Bytecode* args = script->ptrReadPos;
    script->owner1.enemy->flags = *args++;
    return ApiStatus_DONE2;
}

API_CALLABLE(SetSelfEnemyFlagBits) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 bits = *args++;
    s32 mode = evt_get_variable(script, *args++);

    if (mode) {
        enemy->flags |= bits;
    } else {
        enemy->flags &= ~bits;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(EnemyEnableFirstStrike) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(script->owner2.npcID);

    enemy->firstStrikeActive = evt_get_variable(script, *args++);
    enemy->attackOriginPos.x = npc->pos.x;
    enemy->attackOriginPos.y = npc->pos.y;
    enemy->attackOriginPos.z = npc->pos.z;

    return ApiStatus_DONE2;
}

API_CALLABLE(GetSelfNpcID) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, script->owner1.enemy->npcID);
    return ApiStatus_DONE2;
}

API_CALLABLE(ClearDefeatedEnemies) {
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(currentEncounter->defeatFlags); i++) {
        for (j = 0; j < ARRAY_COUNT(currentEncounter->defeatFlags[0]); j++) {
            currentEncounter->defeatFlags[i][j] = 0;
        }
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(GetRemainingEnemyCount) {
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    Bytecode* args = script->ptrReadPos;
    s32 outVar = *args++;
    s32 count = 0;
    s32 i, j;

    for (i = 0; i < encounterStatus->numEncounters; i++) {
        Encounter* encounter = encounterStatus->encounterList[i];
        if (encounter == nullptr) {
            continue;
        }
        for (j = 0; j < encounter->count; j++) {
            if (encounter->enemy[j] != nullptr) {
                count++;
            }
        }
    }

    evt_set_variable(script, outVar, count);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetEnemyFlagBits) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    s32 bits = *args++;
    s32 mode = evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy(npcID);

    if (mode) {
        enemy->flags |= bits;
    } else {
        enemy->flags &= ~bits;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(GetSelfAnimationFromTable) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 animIdx = evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, enemy->animList[animIdx]);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetOwnerInstigatorValue) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;

    enemy->instigatorValue = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleAsScripted) {
    gCurrentEncounter.scriptedBattle = true;
    return ApiStatus_DONE2;
}

API_CALLABLE(GetEncounterTriggerHitTier) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gCurrentEncounter.hitTier);
    return ApiStatus_DONE2;
}

API_CALLABLE(PlaySoundAtEnemy) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    s32 soundID = evt_get_variable(script, *args++);
    s32 upperSoundFlags = evt_get_variable(script, *args++);
    Npc* npc = resolve_npc(script, npcID);

    if (npc == nullptr) {
        return ApiStatus_DONE2;
    }

    ai_enemy_play_sound(npc, soundID, upperSoundFlags);
    return ApiStatus_DONE2;
}

API_CALLABLE(EnemyHasNoSpinReaction) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, script->owner1.enemy->npcSettings->actionFlags & AI_ACTION_NO_SPIN_REACTION);
    return ApiStatus_DONE2;
}

API_CALLABLE(OnPlayerFled) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    b32 skipReaction = evt_get_variable(script, *args++);

    enemy->aiFlags |= AI_FLAG_SUSPEND;

    if (!skipReaction) {
        EffectInstance* emoteEffect;

        if (!(enemy->aiFlags & AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE)) {
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        }

        if (!(enemy->aiFlags & AI_FLAG_SKIP_EMOTE_AFTER_FLEE)) {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 0.0f, -20.0f, 40, &emoteEffect);
        }

        if ((npc->flags & (NPC_FLAG_GRAVITY | NPC_FLAG_JUMPING | NPC_FLAG_FLYING)) == (NPC_FLAG_JUMPING | NPC_FLAG_FLYING)) {
            f32 x = npc->pos.x;
            f32 y = npc->pos.y + npc->collisionHeight;
            f32 z = npc->pos.z;
            f32 a = 100.0f;

            if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &a)) {
                npc->pos.y = y;
            }
            npc->flags &= ~NPC_FLAG_JUMPING;
        }
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetTattleMessage) {
    Bytecode* args = script->ptrReadPos;
    s32 enemyId = evt_get_variable(script, *args++);
    u32 tattleMsg = evt_get_variable(script, *args++);
    Enemy* enemy = get_enemy(enemyId);

    enemy->tattleMsg = tattleMsg;
    return ApiStatus_DONE2;
}
