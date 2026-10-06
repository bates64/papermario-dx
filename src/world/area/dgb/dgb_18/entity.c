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
    Call(MakeEntity, Ref(Entity_Chest), 845, 0, 145, -35, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_DGB18_Chest_MysticalKey)
    Call(AssignScript, Ref(EVS_OpenChest_MysticalKey))
    Return
    End
};
