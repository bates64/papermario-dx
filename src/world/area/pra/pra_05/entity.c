#include "pra_05.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_BlueKey = EVT_OPEN_CHEST(ITEM_BLUE_KEY, GF_PRA05_Chest_BlueKey);

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), 200, 20, 94, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_PRA05_Chest_BlueKey)
    Call(AssignScript, Ref(EVS_OpenChest_BlueKey))
    Return
    End
};
