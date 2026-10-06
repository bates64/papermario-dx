#include "kzn_08.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_DizzyStomp = EVT_OPEN_CHEST(ITEM_DIZZY_STOMP, GF_KZN08_Chest_DizzyStomp);

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), 120, 100, -55, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_KZN08_Chest_DizzyStomp)
    Call(AssignScript, Ref(EVS_OpenChest_DizzyStomp))
    Return
    End
};
