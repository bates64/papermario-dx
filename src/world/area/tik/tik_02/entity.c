#include "tik_02.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest = EVT_OPEN_CHEST(ITEM_SHRINK_STOMP, GF_TIK02_Chest_ShrinkStomp);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_ShrinkStomp)
    Return
    End
};
