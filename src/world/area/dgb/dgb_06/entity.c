#include "dgb_06.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_TubbaKey = EVT_OPEN_CHEST(ITEM_TUBBA_CASTLE_KEY, GF_DGB06_Chest_CastleKey1);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_CastleKey1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
