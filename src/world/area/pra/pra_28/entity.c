#include "pra_28.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_PUpDDown = EVT_OPEN_CHEST(ITEM_P_UP_D_DOWN, GF_PRA28_Chest_PUpDDown);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_PUpDDown)
    Return
    End
};
