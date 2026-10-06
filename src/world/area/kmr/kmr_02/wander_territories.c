#include "kmr_02.h"

EnemyTerritoryWander WanderTerritory0 = {
    .centerPos = { 0, 0, 0 },
    .wanderSize = { 150, 0 },
    .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
    .wanderShape = SHAPE_CYLINDER,
    .detectPos = { 0, 0, 0 },
    .detectSize = { 0, 0 },
    .detectShape = SHAPE_CYLINDER,
    .isFlying = true,
};

EnemyTerritoryWander WanderTerritory1 = {
    .centerPos = { 0, 0, 0 },
    .wanderSize = { 150, 0 },
    .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
    .wanderShape = SHAPE_CYLINDER,
    .detectPos = { 0, 0, 0 },
    .detectSize = { 0, 0 },
    .detectShape = SHAPE_CYLINDER,
    .isFlying = true,
};

EnemyTerritoryWander WanderTerritory2 = {
    .centerPos = { 0, 0, 0 },
    .wanderSize = { 150, 0 },
    .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
    .wanderShape = SHAPE_CYLINDER,
    .detectPos = { 0, 0, 0 },
    .detectSize = { 0, 0 },
    .detectShape = SHAPE_CYLINDER,
    .isFlying = true,
};

EnemyTerritoryWander WanderTerritory3 = {
    .centerPos = { 0, 0, 0 },
    .wanderSize = { 150, 0 },
    .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
    .wanderShape = SHAPE_CYLINDER,
    .detectPos = { 0, 0, 0 },
    .detectSize = { 0, 0 },
    .detectShape = SHAPE_CYLINDER,
    .isFlying = true,
};

EnemyTerritoryWander* WanderTerritories[] = {
    &WanderTerritory0,
    &WanderTerritory1,
    &WanderTerritory2,
    &WanderTerritory3,
};

API_CALLABLE(SetWanderTerritory) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    s32 territoryIndex = evt_get_variable(script, *args++);
    Enemy* enemy = get_enemy(npcID);

    // copy territory to enemy
    enemy->territory->wander = *WanderTerritories[territoryIndex];

    return ApiStatus_DONE2;
}

MobileAISettings AISettings_SwitchedWander = {
    .moveSpeed = 2.0f,
    .moveTime = 15,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcIdle_SwitchedWander = {
    Call(BasicAI_Main, Ref(AISettings_SwitchedWander))
    Return
    End
};
