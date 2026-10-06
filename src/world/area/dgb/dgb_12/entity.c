#include "dgb_12.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_Chest_Interact = EVT_OPEN_CHEST(ITEM_TUBBA_CASTLE_KEY, GF_DGB12_Chest_CastleKey1);

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), -225, 0, -245, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_DGB12_Chest_CastleKey1)
    Call(AssignScript, Ref(EVS_Chest_Interact))
    Return
    End
};
