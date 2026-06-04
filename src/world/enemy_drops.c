#include "common.h"
#include "vars_access.h"
#include "npc.h"

extern s32 gLastRenderTaskCount;

void spawn_drops(Enemy* enemy) {
    EncounterStatus* encounter = &gCurrentEncounter;
    EnemyDrops* drops = enemy->drops;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 pickupDelay;
    s32 availableRenderTasks;
    s32 availableShadows;
    s32 itemToDrop;
    f32 x, y, z;
    f32 threshold;
    f32 chance;
    f32 attempts;
    f32 fraction;
    s32 minCoinBonus;
    s32 maxCoinBonus;
    s32 spawnCounter;
    s32 dropCount;
    s32 totalWeight;
    s32 curWeight;
    s32 angle;
    s32 angleMult;
    s32 i, j;

    availableShadows = 0;
    for (i = 0; i < MAX_SHADOWS; i++) {
        if (get_shadow_by_index(i) == nullptr) {
            availableShadows++;
        }
    }

    spawnCounter = 0;
    availableRenderTasks = 256 - 10 - gLastRenderTaskCount;
    angle = clamp_angle(camera->curYaw + 90.0f);
    x = npc->pos.x;
    y = npc->pos.y + (npc->collisionHeight / 2);
    z = npc->pos.z;

    angleMult = 0;
    pickupDelay = 0;

    // try dropping items

    dropCount = drops->itemDropChance;
    if (drops->itemDropChance > rand_int(100)) {
        totalWeight = 0;

        for (i = 0; i < ARRAY_COUNT(drops->itemDrops); i++) {
            if (drops->itemDrops[i].item != ITEM_NONE) {
                totalWeight += drops->itemDrops[i].weight;
            } else {
                break;
            }
        }

        curWeight = 0;
        dropCount = rand_int(totalWeight);
        itemToDrop = ITEM_NONE;

        for (i = 0; i < ARRAY_COUNT(drops->itemDrops); i++) {
            if (drops->itemDrops[i].item == ITEM_NONE) {
                break;
            }

            curWeight += drops->itemDrops[i].weight;
            if (drops->itemDrops[i].flagIdx > 0) {
                if (get_global_flag(EVT_INDEX_OF_GAME_FLAG(GF_SpawnedItemDrop_00) + drops->itemDrops[i].flagIdx)) {
                    continue;
                }
            }

            if (curWeight >= dropCount) {
                itemToDrop = drops->itemDrops[i].item;
                break;
            }
        }

        if (itemToDrop != ITEM_NONE) {
            make_item_entity(itemToDrop, x, y, z, ITEM_SPAWN_MODE_BATTLE_REWARD, pickupDelay, angle + angleMult * 360, 0);
            spawnCounter++;
            pickupDelay += 2;
            angle += 30.0;
            if (spawnCounter >= 12) {
                angleMult++;
                angle = angleMult * 8;
                spawnCounter = 0;
            }

            if (drops->itemDrops[i].flagIdx >= 0) {
                set_global_flag(EVT_INDEX_OF_GAME_FLAG(GF_SpawnedItemDrop_00) + drops->itemDrops[i].flagIdx);
            }
        }
    }

    if (encounter->dropWhackaBump) {
        encounter->dropWhackaBump = false;
        make_item_entity(ITEM_WHACKAS_BUMP, x, y, z, ITEM_SPAWN_MODE_BATTLE_REWARD, pickupDelay, angle + angleMult * 360, 0);
        spawnCounter++;
        pickupDelay += 2;
        angle += 30.0;
        if (spawnCounter >= 12) {
            angleMult++;
            angle = angleMult * 8;
            spawnCounter = 0;
        }
    }

    // determine number of hearts to drop

    dropCount = 0;
    itemToDrop = ITEM_NONE;
    fraction = gPlayerData.curHP / (f32) gPlayerData.curMaxHP;

    for (i = 0; i <  ARRAY_COUNT(drops->heartDrops); i++) {
        attempts  = drops->heartDrops[i].cutoff;
        threshold = drops->heartDrops[i].generalChance;
        attempts  /= 32767.0f;
        threshold /= 32767.0f;

        if (fraction <= attempts && rand_int(100) <= threshold * 100.0f) {
            attempts = drops->heartDrops[i].attempts;
            chance = drops->heartDrops[i].chancePerAttempt;
            chance /= 32767.0f;
            for (j = 0; j < attempts; j++) {
                if (rand_int(100) <= chance * 100.0f) {
                    dropCount++;
                }
            }
            break;
        }
    }

    if (is_ability_active(ABILITY_HEART_FINDER)) {
        dropCount += 1 + rand_int(2);
    }
    if (enemy->flags & ENEMY_FLAG_NO_DROPS) {
        dropCount = 0;
    }

    // spawn as many of the heart drops as possible

    if (dropCount != 0) {
        itemToDrop = ITEM_HEART;
    }

    if (dropCount * 2 > availableRenderTasks) {
        dropCount = availableRenderTasks / 2;
    }
    availableRenderTasks -= 2 * dropCount;
    if (dropCount > availableShadows) {
        dropCount = availableShadows;
    }

    availableShadows -= dropCount;

    for (i = 0; i < dropCount; i++) {
        make_item_entity(itemToDrop, x, y, z, ITEM_SPAWN_MODE_BATTLE_REWARD, pickupDelay, angle + (angleMult * 360), 0);
        spawnCounter++;
        pickupDelay += 2;
        angle += 30.0;
        if (spawnCounter >= 12) {
            spawnCounter = 0;
            angleMult++;
            angle = angleMult * 8;
        }
    }

    // determine number of flowers to drop

    dropCount = 0;
    itemToDrop = ITEM_NONE;

    if (gPlayerData.curMaxFP > 0) {
        fraction = gPlayerData.curFP / (f32) gPlayerData.curMaxFP;
    } else {
        fraction = 0.0;
    }

    for (i = 0; i <  ARRAY_COUNT(drops->flowerDrops); i++) {
        attempts  = drops->flowerDrops[i].cutoff;
        threshold = drops->flowerDrops[i].generalChance;
        attempts  /= 32767.0f;
        threshold /= 32767.0f;

        if (fraction <= attempts && rand_int(100) <= threshold * 100.0f) {
            attempts = drops->flowerDrops[i].attempts;
            chance = drops->flowerDrops[i].chancePerAttempt;
            chance /= 32767.0f;
            for (j = 0; j < attempts; j++) {
                if (rand_int(100) <= chance * 100.0f) {
                    dropCount++;
                }
            }
            break;
        }
    }

    if (is_ability_active(ABILITY_FLOWER_FINDER)) {
        dropCount += 1 + rand_int(2);
    }
    if (enemy->flags & ENEMY_FLAG_NO_DROPS) {
        dropCount = 0;
    }

    // spawn as many of the flower drops as possible

    if (dropCount != 0) {
        itemToDrop = ITEM_FLOWER_POINT;
    }

    if (dropCount * 2 > availableRenderTasks) {
        dropCount = availableRenderTasks / 2;
    }
    availableRenderTasks -= 2 * dropCount;
    if (dropCount > availableShadows) {
        dropCount = availableShadows;
    }

    availableShadows -= dropCount;

    for (i = 0; i < dropCount; i++) {
        make_item_entity(itemToDrop, x, y, z, ITEM_SPAWN_MODE_BATTLE_REWARD, pickupDelay, angle + (angleMult * 360), 0);
        spawnCounter++;
        pickupDelay += 2;
        angle += 30.0;
        if (spawnCounter >= 12) {
            spawnCounter = 0;
            angleMult++;
            angle = angleMult * 8;
        }
    }

    // determine number of coins to drop

    itemToDrop = ITEM_COIN;

    // swap if max < min
    if (drops->maxCoinBonus < drops->minCoinBonus) {
        maxCoinBonus = drops->minCoinBonus;
        minCoinBonus = drops->maxCoinBonus;
    } else {
        minCoinBonus = drops->minCoinBonus;
        maxCoinBonus = drops->maxCoinBonus;
    }

    if ((minCoinBonus < 0) || (minCoinBonus != maxCoinBonus)) {
        // note: when min < 0, a drop count from the full range will be selected,
        // but all negative values will subsequently be clamped to 0, biasing toward no-drop.
        // this feature is not used by any vanilla enemies.
        dropCount = rand_int(maxCoinBonus - minCoinBonus) + minCoinBonus;
    } else {
        dropCount = minCoinBonus;
    }

    if (dropCount < 0) {
        dropCount = 0;
    }
    dropCount = dropCount + encounter->coinsEarned;

    if (is_ability_active(ABILITY_PAY_OFF)) {
        dropCount += encounter->damageTaken / 2;
        encounter->damageTaken = 0;
    }
    if (encounter->hasMerleeCoinBonus) {
        encounter->hasMerleeCoinBonus = false;
        dropCount *= 3;
    }
    if (is_ability_active(ABILITY_MONEY_MONEY)) {
        dropCount *= 2;
    }
    if (dropCount > 20) {
        dropCount = 20;
    }
    if (enemy->flags & ENEMY_FLAG_NO_DROPS) {
        dropCount = 0;
    }
    if (dropCount * 2 > availableRenderTasks) {
        dropCount = availableRenderTasks / 2;
    }

    // spawn as many of the coin drops as possible

    availableRenderTasks -= 2 * dropCount;

    if (dropCount > availableShadows) {
        dropCount = availableShadows;
    }

    for (i = 0; i < dropCount; i++) {
        make_item_entity(itemToDrop, x, y, z, ITEM_SPAWN_MODE_BATTLE_REWARD, pickupDelay, angle + (angleMult * 360), 0);
        spawnCounter++;
        pickupDelay += 2;
        angle = angle + 30.0;
        if (spawnCounter >= 12) {
            spawnCounter = 0;
            angleMult++;
            angle = angleMult * 8;
        }
    }
}

// does not determine how many coins drop, this is a helper function for Merlee's coin bonus
s32 get_coin_drop_amount(Enemy* enemy) {
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    EnemyDrops* enemyDrops = enemy->drops;
    s32 max = enemyDrops->maxCoinBonus;
    s32 min = enemyDrops->minCoinBonus;
    s32 amt;

    if (max < min) {
        min = enemyDrops->maxCoinBonus;
        max = enemyDrops->minCoinBonus;
    }

    amt = min;

    if ((min < 0) || (min != max)) {
        amt = min + rand_int(max - min);
    }

    if (amt < 0) {
        amt = 0;
    }

    if (is_ability_active(ABILITY_PAY_OFF)) {
        amt += currentEncounter->damageTaken / 2;
    }

    if (currentEncounter->hasMerleeCoinBonus) {
        amt *= 3;
    }

    if (is_ability_active(ABILITY_MONEY_MONEY)) {
        amt *= 2;
    }

    amt += currentEncounter->coinsEarned;

    if (enemy->flags & (ENEMY_FLAG_NO_DROPS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE)) {
        amt = 0;
    }

    if (amt > 20) {
        amt = 20;
    }

    return amt;
}
