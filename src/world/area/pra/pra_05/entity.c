#include "pra_05.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_BlueKey = EVT_OPEN_CHEST(ITEM_BLUE_KEY, GF_PRA05_Chest_BlueKey);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_BlueKey)
    Return
    End
};
