#include "sam_06.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeItemEntity, ITEM_SNOWMAN_SCARF, NPC_DISPOSE_LOCATION, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_ScarfItemID, LVar0)
    Return
    End
};
