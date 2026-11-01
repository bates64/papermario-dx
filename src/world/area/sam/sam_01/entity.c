#include "sam_01.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_AttackFXE = EVT_OPEN_CHEST(ITEM_ATTACK_FX_E, GF_SAM01_Chest_AttackFXE);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_AttackFXE)
    Call(SetEntityCullMode, 1)
    IfLt(GB_StoryProgress, STORY_CH7_MAYOR_MURDER_SOLVED)
        Call(MakeMarkerEntity, $Item_Present_1)
        Set(MV_PresentItemID, LVar0)
    EndIf
    Call(MakeItemEntity, ITEM_SNOWMAN_BUCKET, NPC_DISPOSE_LOCATION, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_BucketItemID, LVar0)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
