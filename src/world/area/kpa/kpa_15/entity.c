#include "kpa_15.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_CastleKey = EVT_OPEN_CHEST(ITEM_BOWSER_CASTLE_KEY, GF_KPA15_Chest_CastleKey2);

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), 220, 30, -100, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_KPA15_Chest_CastleKey2)
    Call(AssignScript, Ref(EVS_OpenChest_CastleKey))
    Return
    End
};

