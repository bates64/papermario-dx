#include "common.h"
#include "battle/battle.h"
#include "battle/script_module.h"

#define GENERIC_FOOD_ITEM -1

// Items in this list must correspond with entries in gBattleItemTable.
s32 ItemKeys[] = {
    GENERIC_FOOD_ITEM,
    ITEM_MUSHROOM,
    ITEM_FIRE_FLOWER,
    ITEM_DUSTY_HAMMER,
    ITEM_POW_BLOCK,
    ITEM_PEBBLE,
    ITEM_VOLT_SHROOM,
    ITEM_THUNDER_RAGE,
    ITEM_SNOWMAN_DOLL,
    ITEM_DRIED_SHROOM,
    ITEM_SHOOTING_STAR,
    ITEM_SLEEPY_SHEEP,
    ITEM_STONE_CAP,
    ITEM_TASTY_TONIC,
    ITEM_THUNDER_BOLT,
    ITEM_SUPER_SHROOM,
    ITEM_ULTRA_SHROOM,
    ITEM_SUPER_SODA,
    ITEM_HUSTLE_DRINK,
    ITEM_STOP_WATCH,
    ITEM_DIZZY_DIAL,
    ITEM_PLEASE_COME_BACK,
    ITEM_EGG_MISSILE,
    ITEM_INSECTICIDE_HERB,
    ITEM_FRIGHT_JAR,
    ITEM_MYSTERY,
    ITEM_REPEL_GEL,
    ITEM_LIFE_SHROOM,
    ITEM_COCONUT,
    ITEM_ELECTRO_POP,
    ITEM_STRANGE_CAKE,
    ITEM_KOOKY_COOKIE,
    ITEM_NONE
};

#define ITEM_SCRIPT(name) { name, BATTLE_SCRIPT_KIND_ITEM, 0 }

static const BattleScriptRef gBattleItemTable[] = {
    ITEM_SCRIPT("food"),
    ITEM_SCRIPT("mushroom"),
    ITEM_SCRIPT("fire_flower"),
    ITEM_SCRIPT("dusty_hammer"),
    ITEM_SCRIPT("pow_block"),
    ITEM_SCRIPT("pebble"),
    ITEM_SCRIPT("volt_shroom"),
    ITEM_SCRIPT("thunder_rage"),
    ITEM_SCRIPT("snowman_doll"),
    ITEM_SCRIPT("mushroom"),
    ITEM_SCRIPT("shooting_star"),
    ITEM_SCRIPT("sleepy_sheep"),
    ITEM_SCRIPT("stone_cap"),
    ITEM_SCRIPT("tasty_tonic"),
    ITEM_SCRIPT("thunder_bolt"),
    ITEM_SCRIPT("mushroom"),
    ITEM_SCRIPT("mushroom"),
    ITEM_SCRIPT("super_soda"),
    ITEM_SCRIPT("hustle_drink"),
    ITEM_SCRIPT("stop_watch"),
    ITEM_SCRIPT("dizzy_dial"),
    ITEM_SCRIPT("please_come_back"),
    ITEM_SCRIPT("egg_missile"),
    ITEM_SCRIPT("insecticide_herb"),
    ITEM_SCRIPT("fright_jar"),
    ITEM_SCRIPT("mystery"),
    ITEM_SCRIPT("repel_gel"),
    ITEM_SCRIPT("life_shroom"),
    ITEM_SCRIPT("coconut"),
    ITEM_SCRIPT("electro_pop"),
    ITEM_SCRIPT("strange_cake"),
    ITEM_SCRIPT("strange_cake"),
};

// Offsets into gBattleItemTable?
u16 D_80293E04[] = {
    1, 31, 1, 5, 1, 2, 9, 3, 9, 3, 9, 1, 10, 6, 10, 6, 10, 4, 11, 8, 11, 8, 11, 4, 12, 3, 12, 3, 12, 1,
};

API_CALLABLE(LoadItemScript) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    s16 itemID = battleStatus->moveArgument;
    ItemData* item = &gItemTable[itemID];
    s32 i = 0;
    s32* itemPtr;

    while (true) {
        if (playerData->invItems[i] == itemID) {
            playerData->invItems[i] = ITEM_NONE;
            break;
        }
        i++;
    }
    sort_consumables();

    if (battleStatus->selectedMoveID == MOVE_DOUBLE_DIP) {
        if (battleStatus->itemUsesLeft == 2) {
            deduct_current_move_fp();
        }
    }

    if (battleStatus->selectedMoveID == MOVE_TRIPLE_DIP) {
        if (battleStatus->itemUsesLeft == 3) {
            deduct_current_move_fp();
        }
    }

    itemPtr = &ItemKeys[0];
    for (i = 0; *itemPtr != ITEM_NONE; i++, itemPtr++) {
        if (*itemPtr == battleStatus->moveArgument) {
            break;
        }
    }

    if (*itemPtr == ITEM_NONE) {
        if (item->typeFlags & ITEM_TYPE_FLAG_FOOD_OR_DRINK) {
            i = 0;
        } else {
            i = 1;
        }
    }

    script->varTablePtr[0] = load_battle_script(&gBattleItemTable[i]);
    script->varTable[1] = false;

    return ApiStatus_DONE2;
}

API_CALLABLE(LoadMysteryItemScript) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* actor = battleStatus->playerActor;
    ItemData* item = &gItemTable[battleStatus->moveArgument];
    SelectableTarget* target;
    s32* itemPtr;
    s32 i;

    battleStatus->curTargetListFlags = item->targetFlags | TARGET_FLAG_PRIMARY_ONLY;
    battleStatus->curAttackElement = 0;

    create_current_pos_target_list(actor);
    target = &actor->targetData[actor->targetIndexList[0]];

    battleStatus->curTargetID = target->actorID;
    battleStatus->curTargetPart = target->partID;

    itemPtr = &ItemKeys[0];
    for (i = 0; *itemPtr != ITEM_NONE; i++, itemPtr++) {
        if (*itemPtr == battleStatus->moveArgument){
            break;
        }
    }

    if (*itemPtr == ITEM_NONE) {
        if (item->typeFlags & ITEM_TYPE_FLAG_FOOD_OR_DRINK) {
            i = 0;
        } else {
            i = 1;
        }
    }

    script->varTablePtr[0] = load_battle_script(&gBattleItemTable[i]);
    script->varTable[1] = true;
    return ApiStatus_DONE2;
}

EvtScript EVS_UseMystery = {
    Wait(2)
    Call(LoadMysteryItemScript)
    ExecWait(LVar0)
    Return
    End
};
