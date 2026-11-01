#include "dgb_18.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_MysticalKey = {
    Set(GF_DGB18_Chest_MysticalKey, true)
    Call(AddItem, ITEM_MYSTICAL_KEY, EVT_IGNORE_ARG)
    Call(SetNpcVar, NPC_Yakkey, 0, 1)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_MysticalKey)
    Return
    End
};
