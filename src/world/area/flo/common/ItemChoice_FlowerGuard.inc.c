#include "common.h"

BSS s32 N(FlowerGuard_ItemChoiceList)[ITEM_NUM_CONSUMABLES + 1];



API_CALLABLE(N(FlowerGuard_MakeItemList)) {
    s32 pos = 0;
    s32 itemID;

    for (itemID = 0; itemID < NUM_ITEMS; itemID++) {
        if (item_is_consumable(itemID)) {
            N(FlowerGuard_ItemChoiceList)[pos++] = itemID;
        }
    }
    N(FlowerGuard_ItemChoiceList)[pos] = ITEM_NONE;

    return ApiStatus_DONE2;
}
