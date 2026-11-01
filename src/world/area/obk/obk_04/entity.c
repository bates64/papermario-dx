#include "obk_04.h"
#include "entity.h"

API_CALLABLE(InitializeKeepAwayItemAlpha) {
    ItemEntity* item = get_item_entity(script->varTable[0]);

    set_item_entity_flags(script->varTable[0], ITEM_ENTITY_FLAG_TRANSPARENT);
    item->alpha = 255;
    return ApiStatus_DONE2;
}

EvtScript EVS_OnSmash_Floor = {
    Set(GF_OBK04_BoardedFloor, true)
    Return
    End
};

EvtScript EVS_OnSmash_Unused = {
    Set(GF_OBK04_UnusedBoardedFloor, true)
    Return
    End
};

EvtScript EVS_OpenGiantChest = {
    Call(DisablePlayerInput, true)
    Set(GF_OBK04_GiantChest, true)
    Exec(EVS_Scene_BoosUnleashed)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $GiantChest)
    Call(MakeItemEntity, ITEM_MENU_BOOTS2, NPC_DISPOSE_LOCATION, ITEM_SPAWN_MODE_DECORATION, 0)
    Call(InitializeKeepAwayItemAlpha)
    Set(MV_KeepAwayItem, LVar0)
    IfEq(GF_OBK04_BoardedFloor, false)
        Call(MakeMarkerEntity, $BoardedFloor_1)
    EndIf
    Call(MakeMarkerEntity, $WoodenCrate_1)
    Call(MakeMarkerEntity, $WoodenCrate_2)
    Call(MakeMarkerEntity, $WoodenCrate_3)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
