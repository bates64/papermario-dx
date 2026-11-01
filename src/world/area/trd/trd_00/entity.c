#include "trd_00.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_Refund = EVT_OPEN_CHEST(ITEM_REFUND, GF_TRD00_Chest_Refund);
EvtScript EVS_OpenChest_FPPlus = EVT_OPEN_CHEST(ITEM_FP_PLUS_B, GF_TRD00_Chest_FPPlusB);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_Refund)
    Call(MakeMarkerEntity, $Chest_FPPlusB)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $SavePoint_2)
    Return
    End
};
