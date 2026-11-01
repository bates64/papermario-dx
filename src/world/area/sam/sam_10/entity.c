#include "sam_10.h"
#include "entity.h"

API_CALLABLE(SetStarStoneItemScale) {
    get_item_entity(script->varTable[0])->scale = 0.8f;
    return ApiStatus_DONE2;
}

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $RedBlock_MegaJump_1)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    IfLt(GB_StoryProgress, STORY_CH7_RAISED_FROZEN_STAIRS)
        Call(DropResizableItemEntity, ITEM_STAR_STONE, NPC_DISPOSE_LOCATION, ITEM_SPAWN_MODE_DECORATION, 0)
        Call(SetStarStoneItemScale)
        Set(MV_StarStoneItemID, LVar0)
    Else
        Call(DropResizableItemEntity, ITEM_STAR_STONE, -117, 179, -55, ITEM_SPAWN_MODE_DECORATION, 0)
        Call(SetStarStoneItemScale)
    EndIf
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
