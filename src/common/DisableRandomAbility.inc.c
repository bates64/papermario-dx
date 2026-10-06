#include "common.h"

static s32 hammer_icons[] = {
    ITEM_MENU_HAMMER1,
    ITEM_MENU_HAMMER2,
    ITEM_MENU_HAMMER3,
};

static s32 hammer_text[] = {
    BTL_MSG_HAMMER_DISABLED_1,
    BTL_MSG_HAMMER_DISABLED_2,
    BTL_MSG_HAMMER_DISABLED_3,
};

static s32 jump_icons[] = {
    ITEM_MENU_BOOTS1,
    ITEM_MENU_BOOTS2,
    ITEM_MENU_BOOTS3,
};

static s32 jump_text[] = {
    BTL_MSG_JUMP_DISABLED_1,
    BTL_MSG_JUMP_DISABLED_2,
    BTL_MSG_JUMP_DISABLED_3,
};

static API_CALLABLE(DisableRandomAbility) {
    Bytecode* args = script->ptrReadPos;
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    s32 turnsLost;
    s32 i = 0;
    s32 temp[3];

    if (battleStatus->hammerLossTurns == -1) {
        temp[i++] = 0;
    }

    if (battleStatus->jumpLossTurns == -1) {
        temp[i++] = 1;
    }

    if (battleStatus->itemLossTurns == -1) {
        temp[i++] = 2;
    }

    turnsLost = rand_int(2) + 2;
    switch (temp[rand_int(i - 1)]) {
        case 0:
            battleStatus->hammerLossTurns = turnsLost;
            evt_set_variable(script, *args++, hammer_icons[playerData->hammerLevel]);
            evt_set_variable(script, *args++, hammer_text[playerData->hammerLevel]);
            break;

        case 1:
            battleStatus->jumpLossTurns = turnsLost;
            evt_set_variable(script, *args++, jump_icons[playerData->bootsLevel]);
            evt_set_variable(script, *args++, jump_text[playerData->bootsLevel]);
            break;

        case 2:
            battleStatus->itemLossTurns = turnsLost;
            evt_set_variable(script, *args++, ITEM_MENU_ITEMS);
            evt_set_variable(script, *args++, BTL_MSG_ITEMS_DISABLED);
            break;
    }

    return ApiStatus_DONE2;
}
