#include "tik_02.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest = EVT_OPEN_CHEST(ITEM_SHRINK_STOMP, GF_TIK02_Chest_ShrinkStomp);

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), 280, -10, 0, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_TIK02_Chest_ShrinkStomp)
    Call(AssignScript, Ref(EVS_OpenChest))
    Return
    End
};
