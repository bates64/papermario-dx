#include "kzn_08.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_DizzyStomp = EVT_OPEN_CHEST(ITEM_DIZZY_STOMP, GF_KZN08_Chest_DizzyStomp);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_DizzyStomp)
    Return
    End
};
