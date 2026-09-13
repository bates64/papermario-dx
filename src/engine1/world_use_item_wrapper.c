#include "common.h"
#include "ld_addrs.h"

extern EvtScript EVS_World_UseItem;

BSS s32 UseItemInvSlot;

s32 use_consumable(s32 invSlot) {
    Evt* script;

    UseItemInvSlot = invSlot;
    invSlot = gPlayerData.invItems[invSlot];
    dma_copy(world_use_item_ROM_START, world_use_item_ROM_END, world_use_item_VRAM);
    script = start_script(&EVS_World_UseItem, EVT_PRIORITY_1, 0);
    script->varTable[10] = invSlot;
    return script->id;
}

void remove_consumable(void) {
    gPlayerData.invItems[UseItemInvSlot] = ITEM_NONE;
    sort_consumables();
}
