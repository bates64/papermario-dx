#include "omo_13.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_PowerPlus = EVT_OPEN_CHEST(ITEM_POWER_PLUS_B, GF_OMO13_Chest_PowerPlusB);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_PowerPlusB)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_MapleSyrup_1)
    Return
    End
};
