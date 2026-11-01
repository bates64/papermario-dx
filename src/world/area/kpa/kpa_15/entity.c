#include "kpa_15.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_CastleKey = EVT_OPEN_CHEST(ITEM_BOWSER_CASTLE_KEY, GF_KPA15_Chest_CastleKey2);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_CastleKey2)
    Return
    End
};
