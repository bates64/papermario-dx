#include "pra_35.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_TripleDip = EVT_OPEN_CHEST(ITEM_TRIPLE_DIP, GF_PRA35_Chest_TripleDip);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_TripleDip)
    Return
    End
};
