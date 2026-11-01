#include "pra_27.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_PalaceKey = EVT_OPEN_CHEST(ITEM_CRYSTAL_PALACE_KEY, GF_PRA27_Chest_PalaceKey);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_PalaceKey)
    Return
    End
};
