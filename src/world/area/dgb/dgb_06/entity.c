#include "dgb_06.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_TubbaKey = EVT_OPEN_CHEST(ITEM_TUBBA_CASTLE_KEY, GF_DGB06_Chest_CastleKey1);

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), -300, 50, -200, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_DGB06_Chest_CastleKey1)
    Call(AssignScript, Ref(EVS_OpenChest_TubbaKey))
    Call(MakeEntity, Ref(Entity_HeartBlock), -125, 60, 175, 0, MAKE_ENTITY_END)
    Return
    End
};
