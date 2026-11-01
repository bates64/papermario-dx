#include "pra_12.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_PDownDUp = EVT_OPEN_CHEST(ITEM_P_DOWN_D_UP, GF_PRA12_Chest_PDownDUp);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_PDownDUp)
    Return
    End
};
