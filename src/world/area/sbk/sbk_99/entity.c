#include "sbk_99.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_SavePoint, 145, 60, -375, 45, MAKE_ENTITY_END)
    Call(MakeEntity, Entity_HeartBlock, 88, 60, -324, 40, MAKE_ENTITY_END)
    Return
    End
};
