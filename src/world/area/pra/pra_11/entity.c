#include "pra_11.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_RedKey = EVT_OPEN_CHEST(ITEM_RED_KEY, GF_PRA11_Chest_RedKey);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_RedKey)
    Return
    End
};
