
#include "kpa_53.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_HeartBlock), -415, 60, -75, 0, MAKE_ENTITY_END)
    Return
    End
};
